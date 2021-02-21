/*
 * UnaryExprAST.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: zbc
 */

#include "UnaryExprAST.h"

UnaryExprAST::UnaryExprAST(CompileUnit *unit, const std::string &op,
                           ExprAST *operand)
    : ExprAST(unit)
{
    this->op      = op;
    this->operand = operand;
}

UnaryExprAST::~UnaryExprAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Value *UnaryExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    return nullptr;
}
