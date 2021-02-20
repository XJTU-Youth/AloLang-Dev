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
    WhileExprAST(CompileUnit *unit, CodeBlockAST *codeblock);
    virtual ~WhileExprAST();
    llvm::Value *Codegen(llvm::IRBuilder<> *builder);
};

#endif /* SRC_AST_WHILEEXPRAST_H_ */
