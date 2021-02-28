/*
 * BinaryExprAST.h
 *
 *  Created on: Feb 12, 2021
 *      Author: zbc
 */

#ifndef COMPILER_AST_BINARYEXPRAST_H_
#define COMPILER_AST_BINARYEXPRAST_H_

#include "ExprAST.h"

class BinaryExprAST : public ExprAST
{
  public:
    BinaryExprAST(CompileUnit *unit, std::string binOP, ExprAST *LHS,
                  ExprAST *RHS);
    virtual ~BinaryExprAST();
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);

    std::string binOP;
    ExprAST *   LHS;
    ExprAST *   RHS;

  private:
    llvm::Value *processInnerBinaryOperator(llvm::Value *L, llvm::Value *R,
                                            llvm::IRBuilder<> *builder);
};

#endif /* COMPILER_AST_BINARYEXPRAST_H_ */
