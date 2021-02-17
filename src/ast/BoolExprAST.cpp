/*
 * BoolExprAST.cpp
 *
 *  Created on: Feb 17, 2021
 *      Author: zbc
 */

#include "BoolExprAST.h"

BoolExprAST::BoolExprAST(CompileUnit *unit, bool val) : ExprAST(unit)
{
    this->val = val;
    type      = "bool";
}

BoolExprAST::~BoolExprAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Value *BoolExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    llvm::IntegerType *type = llvm::IntegerType::get(*unit->context, 1);
    llvm::ConstantInt *res  = llvm::ConstantInt::get(type, val, true);
    return res;
}
