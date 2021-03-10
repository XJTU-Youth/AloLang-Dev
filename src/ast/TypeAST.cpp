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
                 std::vector<TypeAST *> genericTypes, ClassAST *inClass)
    : BaseAST(unit)
{
    this->baseClass    = baseClass;
    this->genericTypes = genericTypes;
    this->pointee      = nullptr;
    this->inClass      = inClass;
}

TypeAST::TypeAST(CompileUnit *unit, TypeAST *pointee) : BaseAST(unit)
{
    this->pointee = pointee;
    this->inClass = nullptr;
}

TypeAST::~TypeAST()
{
    // TODO Auto-generated destructor stub
}
llvm::Type *TypeAST::Codegen()
{
    TypeAST *realType = this;
    if (inClass != nullptr) {
        realType = inClass->getRealType(realType);
    }
    if (pointee == nullptr) {
        //非指针类型
        auto typeAST = unit->types.find(realType->getName());
        if (typeAST == unit->types.end()) {
            //没有找到实例化过的泛型
            auto classAST = unit->classes.find(realType->baseClass);
            if (classAST == unit->classes.end()) {
                CompileError e("can't find class:" + realType->baseClass);
                throw e;
            } else {
                llvm::Type *classType =
                    classAST->second->Codegen(realType->genericTypes);
                return classType;
                //构建泛型
            }
        } else {
            return typeAST->second;
        }
    } else {
        return llvm::PointerType::get(realType->pointee->Codegen(), 0);
    }
}

TypeAST *TypeAST::ParseType(CompileUnit *unit, ClassAST *inClass)
{
    Token token = *unit->icurTok;
    if (token.type != tok_identifier) {
        CompileError e("Expected type but got " + token.dump(), token.source);
        throw e;
    }
    std::string            baseClass = token.tokenValue;
    std::vector<TypeAST *> genericTypes;

    token = unit->next_tok();
    if (token.type == tok_syntax && token.tokenValue == "<") {

        unit->next_tok();
        while (true) {
            genericTypes.push_back(TypeAST::ParseType(unit));
            token = *unit->icurTok;
            if (token.type == tok_syntax) {
                if (token.tokenValue == ",") {
                    token = unit->next_tok();
                } else if (token.tokenValue == ">") {
                    break;
                } else {
                    CompileError e("Unknown token " + token.dump(),
                                   token.source);
                    throw e;
                }
            }
        }
        token = unit->next_tok();
    }
    TypeAST *result = new TypeAST(unit, baseClass, genericTypes, inClass);
    while (token.type == tok_syntax && token.tokenValue == "*") {
        result = new TypeAST(unit, result);
        token  = unit->next_tok();
    }
    return result;
}

std::string TypeAST::getName()
{
    TypeAST *realType = this;
    if (inClass != nullptr) {
        realType = inClass->getRealType(realType);
    }

    std::string name = realType->baseClass;
    if (realType->genericTypes.size() != 0) {
        name += "<";
        for (unsigned int i = 0; i < realType->genericTypes.size() - 1; i++) {
            name += realType->genericTypes[i]->getName() + ",";
        }
        name += realType->genericTypes[realType->genericTypes.size() - 1]
                    ->getName() +
                ">";
    }
    return name;
}

std::string TypeAST::getMangleName()
{
    TypeAST *realType = this;
    if (inClass != nullptr) {
        realType = inClass->getRealType(realType);
    }
    std::stringstream ss;
    if (realType->pointee == nullptr) {
        ss << realType->baseClass.length() << realType->baseClass;
        if (realType->genericTypes.size() != 0) {
            for (unsigned int i = 0; i < realType->genericTypes.size(); i++) {
                std::string name = realType->genericTypes[i]->getName();
                ss << name.length() << name;
            }
        }
        ss << "e";
        return ss.str();
    } else {
        ss << "P";
        ss << realType->pointee->getMangleName();
        return ss.str();
    }
}
