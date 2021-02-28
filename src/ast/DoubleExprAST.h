/*
 * DoubleExprAST.h
 *
 *  Created on: Feb 28, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_DOUBLEEXPRAST_H_
#define SRC_AST_DOUBLEEXPRAST_H_

#include "ExprAST.h"

class DoubleExprAST : public ExprAST
{
  public:
    DoubleExprAST(CompileUnit *unit, double val);
    virtual ~DoubleExprAST();
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);

    double val;
};

#endif /* SRC_AST_DOUBLEEXPRAST_H_ */
