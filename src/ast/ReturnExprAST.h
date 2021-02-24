/*
 * ReturnExprAST.h
 *
 *  Created on: Feb 24, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_RETURNEXPRAST_H_
#define SRC_AST_RETURNEXPRAST_H_

#include "ExprAST.h"

class ReturnExprAST : public ExprAST
{
  public:
    ReturnExprAST(CompileUnit *unit);
    virtual ~ReturnExprAST();
    static ReturnExprAST *     ParseReturnExprAST(CompileUnit * unit,
                                                  CodeBlockAST *codeblock);
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);
    ExprAST *                  returnExpr;
};

#endif /* SRC_AST_RETURNEXPRAST_H_ */
