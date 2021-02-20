/*
 * NumberExprAST.cpp
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#include "IntExprAST.h"
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>

IntExprAST::IntExprAST(CompileUnit *unit, long long val) : ExprAST(unit)
{
    this->val  = val;
    this->type = "int";
}

IntExprAST::~IntExprAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Value *IntExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    llvm::IntegerType *type = llvm::IntegerType::get(*unit->context, 64);
    llvm::ConstantInt *res  = llvm::ConstantInt::get(type, val, true);
    return res;
}
