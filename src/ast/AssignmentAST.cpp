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
    auto varAST = codeblock->namedValues.find(LHS);
    if (varAST == codeblock->namedValues.end()) {
        CompileError e("can't find variable:" + LHS);
        throw e;
    }
    unit->next_tok();
    return new AssignmentAST(unit, varAST->second,
                             ExprAST::ParseExpression(unit, codeblock, false));
}

llvm::Value *AssignmentAST::Codegen(llvm::IRBuilder<> *builder)
{
    llvm::Value *value = RHS->Codegen(builder);
    builder->CreateStore(value, LHS->alloca);
    return value;
}
