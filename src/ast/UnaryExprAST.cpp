/*
 * UnaryExprAST.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: zbc
 */

#include "UnaryExprAST.h"
#include "../CompileError.hpp"

UnaryExprAST::UnaryExprAST(CompileUnit *unit, const std::string &op,
                           ExprAST *operand)
    : ExprAST(unit)
{
    this->op      = op;
    this->operand = operand;
    CompileError e("一元运算符未实现");
    throw e;
}

UnaryExprAST::~UnaryExprAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Value *UnaryExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    return nullptr;
}
