/*
 * CallExprAST.h
 *
 *  Created on: Dec 24, 2020
 *      Author: zbc
 */

#ifndef COMPILER_AST_CALLEXPRAST_H_
#define COMPILER_AST_CALLEXPRAST_H_

#include "ExprAST.h"

class CallExprAST : public ExprAST
{
  public:
    CallExprAST(CompileUnit *unit, const std::string &callee,
                std::vector<ExprAST *> &args);
    virtual ~CallExprAST();
    llvm::Value *Codegen(llvm::IRBuilder<> *builder);

    std::string            callee;
    std::vector<ExprAST *> args;
};

#endif /* COMPILER_AST_CALLEXPRAST_H_ */
