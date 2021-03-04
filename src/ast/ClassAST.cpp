/*
 * ClassAST.cpp
 *
 *  Created on: Feb 22, 2021
 *      Author: zbc
 */

#include "ClassAST.h"
#include "../CompileError.hpp"
#include "TypeAST.h"

ClassAST::ClassAST(CompileUnit *unit, const std::string &className,
                   std::map<std::string, VariableDefExprAST *> members,
                   std::vector<std::string>                    genericTypes)
    : BaseAST(unit)
{
    this->className    = className;
    this->members      = members;
    this->genericTypes = genericTypes;
}

ClassAST::~ClassAST()
{
    // TODO Auto-generated destructor stub
}

ClassAST *ClassAST::ParseClass(CompileUnit *unit)
{
    Token token = unit->next_tok();
    if (token.type != tok_identifier) {
        CompileError e("Expected identifier", token.file, token.lineno);
        throw e;
    }
    std::string              className = token.tokenValue;
    std::vector<std::string> genericTypes;
    std::cout << std::left << std::setw(35)
              << "Class definition found:" << className << std::endl;
    token = unit->next_tok();
    if (token.type == tok_syntax && token.tokenValue == "<") {
        token = unit->next_tok();
        while (!(token.type == tok_syntax && token.tokenValue == ">")) {
            if (token.type == tok_identifier) {
                genericTypes.push_back(token.tokenValue);
            }
            unit->next_tok();
            token = *unit->icurTok;
        }
        token = unit->next_tok();
    }
    if (token.type != tok_syntax || token.tokenValue != "{") {
        CompileError e("Expected {", token.file, token.lineno);
        throw e;
    }
    std::map<std::string, VariableDefExprAST *> members;
    while (true) {
        token = unit->next_tok();
        //解析成员方法，成员变量
        if (token.type == tok_syntax && token.tokenValue == "}") {
            break;
        }
        VariableDefExprAST *memberDef =
            VariableDefExprAST::ParseVar(unit, nullptr);
        members.insert(std::pair<std::string, VariableDefExprAST *>(
            memberDef->idName, memberDef));
    }
    token              = unit->next_tok();
    ClassAST *classAST = new ClassAST(unit, className, members, genericTypes);
    return classAST;
}

TypeAST *ClassAST::getRealType(TypeAST *              type,
                               std::vector<TypeAST *> igenericTypes)
{
    if (type->pointee != nullptr) {
        type->pointee = getRealType(type->pointee, igenericTypes);
    }
    for (unsigned int i = 0; i < type->genericTypes.size(); i++) {
        type->genericTypes[i] =
            getRealType(type->genericTypes[i], igenericTypes);
    }
    auto it = find(genericTypes.begin(), genericTypes.end(), type->name);

    type->initName();

    if (it != genericTypes.end()) {
        //泛型
        int index = it - genericTypes.begin();
        return igenericTypes[index];
    } else {
        return type;
    }
}

llvm::Type *ClassAST::Codegen(std::vector<TypeAST *> igenericTypes)
{
    if (igenericTypes.size() != genericTypes.size()) {
        CompileError e("generic isn't equal");
        throw e;
    }
    std::string name = className;
    if (igenericTypes.size() != 0) {
        name += "<";
        for (unsigned int i = 0; i < igenericTypes.size() - 1; i++) {
            name += igenericTypes[i]->name + ",";
        }
        name += igenericTypes[igenericTypes.size() - 1]->name + ">";
    }

    llvm::StructType *llvm_S =
        llvm::StructType::create(*unit->context, className);
    unit->types.insert(std::pair<std::string, llvm::Type *>(name, llvm_S));
    std::vector<llvm::Type *>                             sMembers;
    std::map<std::string, VariableDefExprAST *>::iterator member_iter;
    for (member_iter = members.begin(); member_iter != members.end();
         member_iter++) {

        VariableDefExprAST *memberVariable = member_iter->second;
        TypeAST *           mType =
            getRealType(memberVariable->variableType, igenericTypes);
        sMembers.push_back(mType->Codegen());
    }
    llvm_S->setBody(sMembers);

    return llvm_S;
}
