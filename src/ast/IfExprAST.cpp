/*
 * IfExprAST.cpp
 *
 *  Created on: Feb 17, 2021
 *      Author: zbc
 */

#include "IfExprAST.h"
#include "../CompileError.hpp"

IfExprAST::IfExprAST(CompileUnit *unit, CodeBlockAST *parent,
                     ExprAST *condition, CodeBlockAST *thenBlock,
                     CodeBlockAST *elseBlock)
    : ExprAST(unit)
{
    this->parent    = parent;
    this->thenBlock = thenBlock;
    this->elseBlock = elseBlock;
    this->condition = condition;
}

IfExprAST::~IfExprAST()
{
    // TODO Auto-generated destructor stub
}

IfExprAST *IfExprAST::ParseIfExpr(CompileUnit *unit, CodeBlockAST *parent)
{
    CompileError e("'if' not implement");
    throw e;
}
