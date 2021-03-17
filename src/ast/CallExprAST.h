/*
 * CallExprAST.h
 *
 *  Created on: Dec 24, 2020
 *      Author: zbc
 */

#ifndef COMPILER_AST_CALLEXPRAST_H_
#define COMPILER_AST_CALLEXPRAST_H_

#include "ExprAST.h"

class FunctionAST;
class CallExprAST : public ExprAST
{
  public:
    CallExprAST(CompileUnit *unit, FunctionAST *parentFunction,
                const std::string &callee, ExprAST *args,
                ExprAST *LHS = nullptr);
    virtual ~CallExprAST();
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);

    FunctionAST *parentFunction;
    std::string  callee;
    bool         Lpointer = false;
    ExprAST *    args;
    ExprAST *    LHS;
};

#endif /* COMPILER_AST_CALLEXPRAST_H_ */
