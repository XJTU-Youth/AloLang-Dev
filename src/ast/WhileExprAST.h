/*
 * WhileExprAST.h
 *
 *  Created on: Feb 20, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_WHILEEXPRAST_H_
#define SRC_AST_WHILEEXPRAST_H_

#include "ExprAST.h"

class WhileExprAST : public ExprAST
{
  public:
    WhileExprAST(CompileUnit *unit, CodeBlockAST *codeblock, ExprAST *condition,
                 CodeBlockAST *body);
    virtual ~WhileExprAST();
    static WhileExprAST *ParseWhileExpr(CompileUnit * unit,
                                        CodeBlockAST *parent);
    llvm::Value *        Codegen(llvm::IRBuilder<> *builder);
    ExprAST *            condition;
    CodeBlockAST *       body;
    CodeBlockAST *       parent;
};

#endif /* SRC_AST_WHILEEXPRAST_H_ */
