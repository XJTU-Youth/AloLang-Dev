/*
 * DoubleExprAST.cpp
 *
 *  Created on: Feb 28, 2021
 *      Author: zbc
 */

#include "DoubleExprAST.h"
#include "TypeAST.h"

DoubleExprAST::DoubleExprAST(CompileUnit *unit, double val) : ExprAST(unit)
{
    this->val = val;
    this->type.push_back(new TypeAST(unit, "double"));
}

DoubleExprAST::~DoubleExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> DoubleExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    this->type.clear();
    this->type.push_back(new TypeAST(unit, "double"));
    std::vector<llvm::Value *> result;
    llvm::Type *               rtype = llvm::Type::getDoubleTy(*unit->context);
    llvm::Value *              res   = llvm::ConstantFP::get(rtype, val);
    result.push_back(res);
    return result;
}
