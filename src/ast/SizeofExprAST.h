/*
 * SizeofExprAST.h
 *
 *  Created on: Mar 6, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_SIZEOFEXPRAST_H_
#define SRC_AST_SIZEOFEXPRAST_H_

#include "ExprAST.h"

class SizeofExprAST : public ExprAST
{
  public:
    SizeofExprAST(CompileUnit *unit, TypeAST *type);
    virtual ~SizeofExprAST();
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);
    TypeAST *                  Stype;
};
#endif /* SRC_AST_SIZEOFEXPRAST_H_ */
