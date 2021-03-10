/*
 * ClassAST.cpp
 *
 *  Created on: Feb 22, 2021
 *      Author: zbc
 */

#include "ClassAST.h"
#include "../CompileError.hpp"
#include "FunctionAST.h"
#include "TypeAST.h"

ClassAST::ClassAST(CompileUnit *unit, const std::string &className,
                   std::vector<VariableDefExprAST *> members,
                   std::vector<FunctionAST *>        functions,
                   std::vector<std::string>          genericTypes)
    : BaseAST(unit)
{
    this->className    = className;
    this->omembers     = members;
    this->functions    = functions;
    this->genericTypes = genericTypes;
    for (VariableDefExprAST *member : members) {
        this->members.insert(std::pair<std::string, VariableDefExprAST *>(
            member->idName, member));
    }
}

ClassAST::~ClassAST()
{
    // TODO Auto-generated destructor stub
}

ClassAST *ClassAST::ParseClass(CompileUnit *unit)
{
    Token token = unit->next_tok();
    if (token.type != tok_identifier) {
        CompileError e("Expected identifier", token.source);
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
        CompileError e("Expected {", token.source);
        throw e;
    }

    ClassAST *classAST =
        new ClassAST(unit, className, std::vector<VariableDefExprAST *>(),
                     std::vector<FunctionAST *>(), genericTypes);
    unit->next_tok();
    while (true) {
        //解析成员方法，成员变量
        token = *(unit->icurTok);
        if (token.type == tok_syntax && token.tokenValue == "}") {
            break;
        }
        if (token.type == tok_fun) {
            FunctionAST *funDef = FunctionAST::ParseFunction(unit, classAST);
            classAST->functions.push_back(funDef);

        } else {
            VariableDefExprAST *memberDef =
                VariableDefExprAST::ParseVar(unit, nullptr);
            classAST->omembers.push_back(memberDef);
            classAST->members.insert(
                std::pair<std::string, VariableDefExprAST *>(memberDef->idName,
                                                             memberDef));

            unit->next_tok();
        }
    }

    token = unit->next_tok();
    return classAST;
}

TypeAST *ClassAST::getRealType(const TypeAST *        type,
                               std::vector<TypeAST *> igenericTypes)
{
    TypeAST *realType = new TypeAST(unit, type->baseClass);
    if (type->pointee != nullptr) {
        realType->pointee = getRealType(type->pointee, igenericTypes);
    }
    for (unsigned int i = 0; i < type->genericTypes.size(); i++) {
        realType->genericTypes.push_back(
            getRealType(type->genericTypes[i], igenericTypes));
    }
    auto it = find(genericTypes.begin(), genericTypes.end(), type->baseClass);

    if (it != genericTypes.end()) {
        //泛型
        int index = it - genericTypes.begin();
        return igenericTypes[index];
    } else {
        return realType;
    }
}

TypeAST *ClassAST::getRealType(const TypeAST *type)
{
    return getRealType(type, this->igenericTypes);
}

std::string ClassAST::getRealName(std::vector<TypeAST *> igenericTypes)
{
    std::string name = className;
    if (igenericTypes.size() != 0) {
        name += "<";
        for (unsigned int i = 0; i < igenericTypes.size() - 1; i++) {
            name += igenericTypes[i]->getName() + ",";
        }
        name += igenericTypes[igenericTypes.size() - 1]->getName() + ">";
    }
    return name;
}

std::string ClassAST::getRealNameForMangle(std::vector<TypeAST *> igenericTypes)
{
    std::stringstream ss;
    ss << "C" << className.length() << className;
    if (igenericTypes.size() != 0) {
        for (unsigned int i = 0; i < igenericTypes.size() - 1; i++) {
            std::string typeMangleName = igenericTypes[i]->getMangleName();
            ss << typeMangleName.length() << typeMangleName;
        }
    }
    ss << "E";
    return ss.str();
}

llvm::Type *ClassAST::Codegen(std::vector<TypeAST *> igenericTypes)
{
    if (igenericTypes.size() != genericTypes.size()) {
        CompileError e("generic isn't equal");
        throw e;
    }
    this->igenericTypes    = igenericTypes;
    std::string       name = getRealName(igenericTypes);
    llvm::StructType *llvm_S =
        llvm::StructType::create(*unit->context, className);
    unit->types.insert(std::pair<std::string, llvm::Type *>(name, llvm_S));
    std::vector<llvm::Type *> sMembers;
    for (VariableDefExprAST *member : this->omembers) {
        TypeAST *mType = getRealType(member->variableType, igenericTypes);
        sMembers.push_back(mType->Codegen());
    }
    llvm_S->setBody(sMembers);
    for (FunctionAST *function : functions) {
        function->Codegen(igenericTypes);
    }

    return llvm_S;
}
