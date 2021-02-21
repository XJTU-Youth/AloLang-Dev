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
    llvm::Value *Codegen(llvm::IRBuilder<> *builder);

    std::string binOP;
    ExprAST *   LHS;
    ExprAST *   RHS;
};

#endif /* COMPILER_AST_BINARYEXPRAST_H_ */
