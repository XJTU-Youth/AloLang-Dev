/*
 * StringExprAST.h
 *
 *  Created on: Mar 14, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_STRINGEXPRAST_H_
#define SRC_AST_STRINGEXPRAST_H_

#include "ExprAST.h"

class StringExprAST : public ExprAST
{
  public:
    StringExprAST(CompileUnit *unit, const std::string &str);
    virtual ~StringExprAST();
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);
    std::string                str;
};

#endif /* SRC_AST_STRINGEXPRAST_H_ */
