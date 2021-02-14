/*
 * NumberExprAST.h
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#ifndef COMPILER_AST_INTEXPRAST_H_
#define COMPILER_AST_INTEXPRAST_H_

#include "ExprAST.h"

class IntExprAST : public ExprAST
{
  public:
    IntExprAST(CompileUnit *unit, long long val);
    virtual ~IntExprAST();
    llvm::Value *Codegen(llvm::IRBuilder<> *builder);

    long long val;
};

#endif /* COMPILER_AST_INTEXPRAST_H_ */
