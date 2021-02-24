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
        this->type.push_back(new TypeAST(unit, "bool"));
    } else {
        CompileError e("一元运算符:" + op + "未实现");
        throw e;
    }
}

UnaryExprAST::~UnaryExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> UnaryExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> result;
    if (op == "!") {

        std::vector<llvm::Value *> Rs = operand->Codegen(builder);
        if (Rs.size() != 1) {
            CompileError e("Unary Expr length != 1");
            throw e;
        }
        result.push_back(builder->CreateXor(Rs[0], 1));
    }
    return result;
}
