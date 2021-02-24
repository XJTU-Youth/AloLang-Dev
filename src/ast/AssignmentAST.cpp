/*
 * AssignmentAST.cpp
 *
 *  Created on: Feb 17, 2021
 *      Author: zbc
 */

#include "AssignmentAST.h"
#include "../CompileError.hpp"
#include "CodeBlockAST.h"
#include "VariableExprAST.h"

AssignmentAST::AssignmentAST(CompileUnit *                  unit,
                             std::vector<VariableExprAST *> LHS, ExprAST *RHS)
    : ExprAST(unit)
{
    this->LHS = LHS;
    this->RHS = RHS;
}

AssignmentAST::~AssignmentAST()
{
    // TODO Auto-generated destructor stub
}

AssignmentAST *AssignmentAST::ParseAssignment(CompileUnit * unit,
                                              CodeBlockAST *codeblock)
{
    std::vector<VariableExprAST *> LHS; //左侧变量
    Token                          token = *unit->icurTok;

    while (true) {
        if (token.type == tok_identifier) {
            LHS.push_back(
                new VariableExprAST(unit, codeblock, token.tokenValue));
        } else if (token.type == tok_syntax) {
            if (token.tokenValue == "=") {
                break;
            }
        }
        token = unit->next_tok();
    }
    unit->next_tok();
    return new AssignmentAST(unit, LHS,
                             ExprAST::ParseExpression(unit, codeblock, false));
}

std::vector<llvm::Value *> AssignmentAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> RHSV = RHS->Codegen(builder);
    if (RHSV.size() != LHS.size()) {
        CompileError e("the length of expression isn't equal.");
        throw e;
    }
    for (unsigned int i = 0; i < LHS.size(); i++) {
        builder->CreateStore(RHSV[i],
                             LHS[i]->getAlloca()); // todo:对函数参数赋值
    }
    return std::vector<llvm::Value *>();
}
