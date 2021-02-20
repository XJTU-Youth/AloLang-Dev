/*
 * BinaryExprAST.cpp
 *
 *  Created on: Feb 12, 2021
 *      Author: zbc
 */

#include "BinaryExprAST.h"
#include "../CompileError.hpp"

BinaryExprAST::BinaryExprAST(CompileUnit *unit, std::string binOP, ExprAST *LHS,
                             ExprAST *RHS)
    : ExprAST(unit)
{
    this->binOP = binOP;
    this->LHS   = LHS;
    this->RHS   = RHS;
    this->type  = LHS->type;
}

BinaryExprAST::~BinaryExprAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Value *BinaryExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    llvm::Value *L = LHS->Codegen(builder);
    llvm::Value *R = RHS->Codegen(builder);
    if (L == nullptr || R == 0)
        return 0;
    if (binOP == "+") {
        return builder->CreateAdd(L, R);
    } else if (binOP == "-") {
        return builder->CreateSub(L, R);
    } else if (binOP == "*") {
        return builder->CreateMul(L, R);
    } else if (binOP == "/") {
        return builder->CreateFDiv(L, R);
    } else if (binOP == "==") {
        return builder->CreateICmpEQ(L, R);
    } else if (binOP == "!=") {
        return builder->CreateICmpNE(L, R);
    } else if (binOP == ">") {
        return builder->CreateICmpSGT(L, R);
    } else if (binOP == "<") {
        return builder->CreateICmpSLT(L, R);
    } else if (binOP == ">=") {
        return builder->CreateICmpSGE(L, R);
    } else if (binOP == "<=") {
        return builder->CreateICmpSLE(L, R);
    } else {
        CompileError e("Unknown operator:" + binOP);
        throw e;
    }
}
