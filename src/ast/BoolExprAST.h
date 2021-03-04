/*
 * BoolExprAST.h
 *
 *  Created on: Feb 17, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_BOOLEXPRAST_H_
#define SRC_AST_BOOLEXPRAST_H_

#include "ExprAST.h"

class BoolExprAST : public ExprAST
{
  public:
    BoolExprAST(CompileUnit *unit, bool val);
    virtual ~BoolExprAST();
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);
    bool                       val;
};

#endif /* SRC_AST_BOOLEXPRAST_H_ */
