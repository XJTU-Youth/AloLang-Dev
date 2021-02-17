/*
 * IfExprAST.h
 *
 *  Created on: Feb 17, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_IFEXPRAST_H_
#define SRC_AST_IFEXPRAST_H_

#include "ExprAST.h"

class CodeBlockAST;
class IfExprAST : public ExprAST
{
  public:
    IfExprAST(CompileUnit *unit, CodeBlockAST *parent, ExprAST *condition,
              CodeBlockAST *thenBlock, CodeBlockAST *elseBlock);
    virtual ~IfExprAST();
    static IfExprAST *ParseIfExpr(CompileUnit *unit, CodeBlockAST *parent);
    ExprAST *         condition;
    CodeBlockAST *    thenBlock;
    CodeBlockAST *    elseBlock;
    CodeBlockAST *    parent;
};

#endif /* SRC_AST_IFEXPRAST_H_ */
