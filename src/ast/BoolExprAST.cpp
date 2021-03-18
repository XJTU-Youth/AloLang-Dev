/*
 * BoolExprAST.cpp
 *
 *  Created on: Feb 17, 2021
 *      Author: zbc
 */

#include "BoolExprAST.h"
#include "TypeAST.h"

BoolExprAST::BoolExprAST(CompileUnit *unit, bool val) : ExprAST(unit)
{
    this->val = val;
    type.push_back(new TypeAST(unit, "bool"));
}

BoolExprAST::~BoolExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> BoolExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    this->type.clear();
    this->type.push_back(new TypeAST(unit, "bool"));
    std::vector<llvm::Value *> result;
    llvm::IntegerType *        type = llvm::IntegerType::get(*unit->context, 1);
    llvm::ConstantInt *        res  = llvm::ConstantInt::get(type, val, true);
    result.push_back(res);
    return result;
}
