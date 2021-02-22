/*
 * UnaryExprAST.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: zbc
 */

#include "UnaryExprAST.h"
#include "../CompileError.hpp"
#include "TypeAST.h"

UnaryExprAST::UnaryExprAST(CompileUnit *unit, const std::string &op,
                           ExprAST *operand)
    : ExprAST(unit)
{
    this->op      = op;
    this->operand = operand;
    if (op == "!") {
        this->type = new TypeAST(unit, "bool");
    } else {
        CompileError e("一元运算符:" + op + "未实现");
        throw e;
    }
}

UnaryExprAST::~UnaryExprAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Value *UnaryExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    if (op == "!") {
        return builder->CreateXor(operand->Codegen(builder), 1);
    }
    return nullptr;
}
