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
    VariableExprAST(CompileUnit *unit, const std::string &idName,
                    const std::string &type, ExprAST *initValue,
                    int argID = -1);
    virtual ~VariableExprAST();
    static VariableExprAST *ParseVar(CompileUnit *unit, CodeBlockAST *codeblock,
                                     std::string idName, std::string type);
    llvm::Value *           Codegen(llvm::IRBuilder<> *builder);
    std::string             idName;
    llvm::Value *           alloca;
    ExprAST *               initValue;
    int                     argID; //函数的参数号，函数内变量为-1
};

#endif /* COMPILER_AST_VARIABLEEXPRAST_H_ */
