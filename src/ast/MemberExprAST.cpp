/*
 * MemberExprAST.cpp
 *
 *  Created on: Feb 25, 2021
 *      Author: zbc
 */

#include "MemberExprAST.h"

MemberExprAST::MemberExprAST(CompileUnit *unit, ExprAST *expr) : ExprAST(unit)
{
    this->expr = expr;
}

MemberExprAST::~MemberExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> MemberExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> result;
    return result;
}
