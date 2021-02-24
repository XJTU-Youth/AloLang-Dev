/*
 * EmptyExprAST.h
 *
 *  Created on: Feb 24, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_EMPTYEXPRAST_H_
#define SRC_AST_EMPTYEXPRAST_H_

#include "ExprAST.h"

class EmptyExprAST : public ExprAST
{
  public:
    EmptyExprAST(CompileUnit *unit);
    virtual ~EmptyExprAST();
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);
};

#endif /* SRC_AST_EMPTYEXPRAST_H_ */
