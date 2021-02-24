/*
 * UnaryExprAST.h
 *
 *  Created on: Feb 21, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_UNARYEXPRAST_H_
#define SRC_AST_UNARYEXPRAST_H_

#include "ExprAST.h"

class UnaryExprAST : public ExprAST
{
  public:
    UnaryExprAST(CompileUnit *unit, const std::string &op, ExprAST *operand);
    virtual ~UnaryExprAST();
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);
    std::string                op;
    ExprAST *                  operand;
};

#endif /* SRC_AST_UNARYEXPRAST_H_ */
