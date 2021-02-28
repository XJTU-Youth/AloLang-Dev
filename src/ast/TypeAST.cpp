/*
 * TypeAST.cpp
 *
 *  Created on: Feb 16, 2021
 *      Author: zbc
 */

#include "TypeAST.h"
#include "../CompileError.hpp"
#include "ClassAST.h"
#include "CompileUnit.h"

TypeAST::TypeAST(CompileUnit *unit, std::string baseClass,
                 std::vector<TypeAST *> genericTypes)
    : BaseAST(unit)
{
    this->baseClass    = baseClass;
    this->genericTypes = genericTypes;
    this->pointee      = nullptr;
    //生成name
    this->name = baseClass;
    if (genericTypes.size() != 0) {
        this->name += "<";
        for (unsigned int i = 0; i < genericTypes.size() - 1; i++) {
            this->name += genericTypes[i]->name + ",";
        }
        this->name += genericTypes[genericTypes.size() - 1]->name + ">";
    }
}

TypeAST::TypeAST(CompileUnit *unit, TypeAST *pointee) : BaseAST(unit)
{
    this->pointee = pointee;
    //生成name
    this->name = pointee->name + "*";
}

TypeAST::~TypeAST()
{
    // TODO Auto-generated destructor stub
}
llvm::Type *TypeAST::Codegen()
{
    if (pointee == nullptr) {
        //非指针类型
        auto typeAST = unit->types.find(name);
        if (typeAST == unit->types.end()) {
            //没有找到实例化过的泛型
            auto classAST = unit->classes.find(baseClass);
            if (classAST == unit->classes.end()) {
                CompileError e("can't find class:" + baseClass);
                throw e;
            } else {
                llvm::Type *classType = classAST->second->Codegen(genericTypes);
                unit->types.insert(
                    std::pair<std::string, llvm::Type *>(name, classType));
                return classType;
                //构建泛型
            }
        } else {
            return typeAST->second;
        }
    } else {
        return llvm::PointerType::get(pointee->Codegen(), 0);
    }
}

TypeAST *TypeAST::ParseType(CompileUnit *unit)
{
    Token token = *unit->icurTok;
    if (token.type != tok_identifier) {
        CompileError e("Expected type but got " + token.dump());
        throw e;
    }
    std::string            baseClass = token.tokenValue;
    std::vector<TypeAST *> genericTypes;

    token = unit->next_tok();
    if (token.type == tok_syntax && token.tokenValue == "<") {

        unit->next_tok();
        while (!(token.type == tok_syntax && token.tokenValue == ">")) {
            genericTypes.push_back(TypeAST::ParseType(unit));
            token = *unit->icurTok;
        }
        token = unit->next_tok();
    }
    TypeAST *result = new TypeAST(unit, baseClass, genericTypes);
    while (token.type == tok_syntax && token.tokenValue == "*") {
        result = new TypeAST(unit, result);
        token  = unit->next_tok();
    }
    return result;
}
