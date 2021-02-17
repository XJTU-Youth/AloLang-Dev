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
                    const std::string &idName, const std::string &type,
                    ExprAST *initValue);
    virtual ~VariableExprAST();
    static VariableExprAST *ParseVar(CompileUnit *unit, CodeBlockAST *codeblock,
                                     std::string idName, std::string type);
    llvm::Value *           Codegen(llvm::IRBuilder<> *builder);
    std::string             idName;
    CodeBlockAST *          codeblock;
    llvm::AllocaInst *      alloca;
    ExprAST *               initValue;
};

#endif /* COMPILER_AST_VARIABLEEXPRAST_H_ */
