/*
 * VariableExprAST.h
 *
 *  Created on: Jan 23, 2021
 *      Author: zbc
 */

#ifndef COMPILER_AST_VARIABLEEXPRAST_H_
#define COMPILER_AST_VARIABLEEXPRAST_H_
#include "ExprAST.h"

class VariableExprAST : public ExprAST
{
  public:
    VariableExprAST(CompileUnit *unit, CodeBlockAST *codeblock,
                    const std::string &idName);
    virtual ~VariableExprAST();
    virtual llvm::Value *      getAlloca(llvm::IRBuilder<> *builder);
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);
    std::string                idName;
    CodeBlockAST *             codeblock;

  private:
    llvm::Value *alloca;
};

#endif /* COMPILER_AST_VARIABLEEXPRAST_H_ */
