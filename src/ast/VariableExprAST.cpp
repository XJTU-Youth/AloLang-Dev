/*
 * VariableExprAST.cpp
 *
 *  Created on: Jan 23, 2021
 *      Author: zbc
 */

#include "VariableExprAST.h"

#include "../CompileError.hpp"
#include "CodeBlockAST.h"
#include "IntExprAST.h"
#include "TypeAST.h"
#include <iostream>

VariableExprAST::VariableExprAST(CompileUnit *unit, CodeBlockAST *codeblock,
                                 const std::string &idName)
    : ExprAST(unit)
{
    this->idName    = idName;
    this->codeblock = codeblock;
    this->alloca    = nullptr;
}

VariableExprAST::~VariableExprAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Value *VariableExprAST::getAlloca(llvm::IRBuilder<> *builder)
{
    if (alloca != nullptr) {
        return alloca;
    }
    //找局部变量
    CodeBlockAST *curCodeBlock = codeblock;
    while (curCodeBlock != nullptr) {
        auto varAST = curCodeBlock->namedValues.find(idName);
        if (varAST == curCodeBlock->namedValues.end()) {
            curCodeBlock = curCodeBlock->parent;
        } else {
            alloca = varAST->second.second;
            type.push_back(varAST->second.first);
            if (varAST->second.first->name == "") {
                std::cout << "fuck" << std::endl;
            }
            return alloca;
        }
    }
    //找全局变量
    auto gVar = unit->globalVariablesValue.find(idName);
    if (gVar == unit->globalVariablesValue.end()) {
        CompileError e("can't find variable:" + idName);
        throw e;
    } else {
        type.push_back(gVar->second.first);
        alloca = gVar->second.second;
        return alloca;
    }
}

std::vector<llvm::Value *> VariableExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> result;
    result.push_back(builder->CreateLoad(getAlloca(builder)));
    return result;
}
