/*
 * WhileExprAST.cpp
 *
 *  Created on: Feb 20, 2021
 *      Author: zbc
 */

#include "WhileExprAST.h"

WhileExprAST::WhileExprAST(CompileUnit *unit, CodeBlockAST *codeblock)
    : ExprAST(unit)
{
}

WhileExprAST::~WhileExprAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Value *WhileExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    return nullptr;
}
