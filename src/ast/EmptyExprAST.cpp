/*
 * EmptyExprAST.cpp
 *
 *  Created on: Feb 24, 2021
 *      Author: zbc
 */

#include "EmptyExprAST.h"

EmptyExprAST::EmptyExprAST(CompileUnit *unit) : ExprAST(unit)
{
    // TODO Auto-generated constructor stub
}

EmptyExprAST::~EmptyExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> EmptyExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    return std::vector<llvm ::Value *>();
}
