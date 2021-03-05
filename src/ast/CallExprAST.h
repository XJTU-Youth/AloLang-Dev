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
    CallExprAST(CompileUnit *unit, const std::string &callee, ExprAST *args,
                ExprAST *LHS = nullptr);
    virtual ~CallExprAST();
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);

    std::string callee;
    ExprAST *   args;
    ExprAST *   LHS;
};

#endif /* COMPILER_AST_CALLEXPRAST_H_ */
