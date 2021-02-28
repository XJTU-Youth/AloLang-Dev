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
}

BinaryExprAST::~BinaryExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> BinaryExprAST::Codegen(llvm::IRBuilder<> *builder)
{

    std::vector<llvm::Value *> L = LHS->CodegenChain(builder);
    std::vector<llvm::Value *> R = RHS->CodegenChain(builder);
    std::vector<llvm::Value *> result;
    if (L.size() != 1 || R.size() != 1) {
        CompileError e("Bin Expr length != 1");
        throw e;
    }
    std::string LHStype = LHS->type[0]->name;
    std::string RHStype = RHS->type[0]->name;
    auto        operate = unit->binOperators.find({LHStype, RHStype, binOP});
    if (operate == unit->binOperators.end()) {
        CompileError e("Unknown operator " + binOP + "with type " + LHStype +
                       " and " + RHStype);
        throw e;
    }
    this->type.push_back(operate->second.second);
    if (operate->second.first == nullptr) {
        //内置运算符
        if (binOP == "+") {
            result.push_back(builder->CreateAdd(L[0], R[0]));
        } else if (binOP == "-") {
            result.push_back(builder->CreateSub(L[0], R[0]));
        } else if (binOP == "*") {
            result.push_back(builder->CreateMul(L[0], R[0]));
        } else if (binOP == "/") {
            result.push_back(builder->CreateSDiv(L[0], R[0]));
        } else if (binOP == "%") {
            result.push_back(builder->CreateSRem(L[0], R[0]));
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
        }
    } else {
        //用户定义运算符
        CompileError e("User-def operator not implemented");
        throw e;
    }
    return result;
}
