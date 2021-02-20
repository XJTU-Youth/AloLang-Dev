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

AssignmentAST::AssignmentAST(CompileUnit *unit, VariableExprAST *LHS,
                             ExprAST *RHS)
    : ExprAST(unit)
{
    this->LHS = LHS;
    this->RHS = RHS;
}

AssignmentAST::~AssignmentAST()
{
    // TODO Auto-generated destructor stub
}

AssignmentAST *AssignmentAST::ParseAssignment(CompileUnit *      unit,
                                              CodeBlockAST *     codeblock,
                                              const std::string &LHS)
{

    unit->next_tok();
    return new AssignmentAST(unit, new VariableExprAST(unit, codeblock, LHS),
                             ExprAST::ParseExpression(unit, codeblock, false));
}

llvm::Value *AssignmentAST::Codegen(llvm::IRBuilder<> *builder)
{
    llvm::Value *value = RHS->Codegen(builder);

    builder->CreateStore(value, LHS->getAlloca()); // todo:对函数参数赋值
    return value;
}
