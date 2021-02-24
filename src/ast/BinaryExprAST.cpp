/*
 * BinaryExprAST.cpp
 *
 *  Created on: Feb 12, 2021
 *      Author: zbc
 */

#include "BinaryExprAST.h"
#include "../CompileError.hpp"
#include "TypeAST.h"

BinaryExprAST::BinaryExprAST(CompileUnit *unit, std::string binOP, ExprAST *LHS,
                             ExprAST *RHS)
    : ExprAST(unit)
{
    this->binOP = binOP;
    this->LHS   = LHS;
    this->RHS   = RHS;
    // todo:类型检查
    this->type = LHS->type;
    //整理此段代码，将操作抽象
    if (binOP == "==") {
        this->type.push_back(new TypeAST(unit, "bool"));
    } else if (binOP == "!=") {
        this->type.push_back(new TypeAST(unit, "bool"));
    } else if (binOP == ">") {
        this->type.push_back(new TypeAST(unit, "bool"));
    } else if (binOP == "<") {
        this->type.push_back(new TypeAST(unit, "bool"));
    } else if (binOP == ">=") {
        this->type.push_back(new TypeAST(unit, "bool"));
    } else if (binOP == "<=") {
        this->type.push_back(new TypeAST(unit, "bool"));
    }
}

BinaryExprAST::~BinaryExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> BinaryExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> L = LHS->Codegen(builder);
    std::vector<llvm::Value *> R = RHS->Codegen(builder);
    std::vector<llvm::Value *> result;
    if (L.size() != 1 || R.size() != 1) {
        CompileError e("Bin Expr length != 1");
        throw e;
    }
    if (binOP == "+") {
        result.push_back(builder->CreateAdd(L[0], R[0]));
    } else if (binOP == "-") {
        result.push_back(builder->CreateSub(L[0], R[0]));
    } else if (binOP == "*") {
        result.push_back(builder->CreateMul(L[0], R[0]));
    } else if (binOP == "/") {
        result.push_back(builder->CreateFDiv(L[0], R[0]));
    } else if (binOP == "==") {
        result.push_back(builder->CreateICmpEQ(L[0], R[0]));
    } else if (binOP == "!=") {
        result.push_back(builder->CreateICmpNE(L[0], R[0]));
    } else if (binOP == ">") {
        result.push_back(builder->CreateICmpSGT(L[0], R[0]));
    } else if (binOP == "<") {
        result.push_back(builder->CreateICmpSLT(L[0], R[0]));
    } else if (binOP == ">=") {
        result.push_back(builder->CreateICmpSGE(L[0], R[0]));
    } else if (binOP == "<=") {
        result.push_back(builder->CreateICmpSLE(L[0], R[0]));
    } else {
        CompileError e("Unknown operator:" + binOP);
        throw e;
    }
    return result;
}
