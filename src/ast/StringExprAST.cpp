/*
 * StringExprAST.cpp
 *
 *  Created on: Mar 14, 2021
 *      Author: zbc
 */

#include "StringExprAST.h"
#include "../CompileError.hpp"
#include "TypeAST.h"

StringExprAST::StringExprAST(CompileUnit *unit, const std::string &str)
    : ExprAST(unit)
{
    // TODO Auto-generated constructor stub
}

StringExprAST::~StringExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> StringExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    type.clear();
    this->type.push_back(new TypeAST(unit, "string"));
    std::vector<llvm::Value *> result;
    CompileError               e("字符串字面值未实现", source);
    throw e;
    // result.push_back(res);
    return result;
}
