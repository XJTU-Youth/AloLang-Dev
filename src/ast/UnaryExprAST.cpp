/*
 * UnaryExprAST.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: zbc
 */

#include "UnaryExprAST.h"
#include "../CompileError.hpp"
#include "TypeAST.h"
#include "VariableExprAST.h"

UnaryExprAST::UnaryExprAST(CompileUnit *unit, const std::string &op,
                           ExprAST *operand)
    : ExprAST(unit)
{
    this->op      = op;
    this->operand = operand;
    /*if (op == "!") {
        this->type.push_back(new TypeAST(unit, "bool"));
    } else if (op == "&") {
        this->type.push_back(new TypeAST(unit, "bool"));
    } else {
        CompileError e("一元运算符:" + op + "未实现");
        throw e;
    }*/
}

UnaryExprAST::~UnaryExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> UnaryExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> result;
    if (op == "&") {
        if (VariableExprAST *v = dynamic_cast<VariableExprAST *>(operand)) {
            result.push_back(v->getAlloca());
            this->type.push_back(new TypeAST(unit, operand->type[0]));
        } else {
            CompileError e("& can only be used with variable");
            throw e;
        }
    } else {
        //值操作
        std::vector<llvm::Value *> Rs = operand->CodegenChain(builder);
        if (Rs.size() != 1) {
            CompileError e("Unary Expr length != 1");
            throw e;
        }

        if (op == "!") {
            this->type.push_back(new TypeAST(unit, "bool"));
            result.push_back(builder->CreateXor(Rs[0], 1));
        } else if (op == "*") {
            if (operand->type[0]->pointee == nullptr) {
                CompileError e("operator * must be used on pointer");
                throw e;
            }
            this->type.push_back(operand->type[0]->pointee);
            result.push_back(builder->CreateLoad(Rs[0]));
        } else {
            CompileError e("一元运算符:" + op + "未实现");
            throw e;
        }
    }
    return result;
}
