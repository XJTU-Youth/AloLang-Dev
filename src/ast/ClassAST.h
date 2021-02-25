/*
 * ClassAST.h
 *
 *  Created on: Feb 22, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_CLASSAST_H_
#define SRC_AST_CLASSAST_H_

#include "BaseAST.h"
#include "VariableDefExprAST.h"

class ClassAST : public BaseAST
{
  public:
    ClassAST(CompileUnit *unit, const std::string &className,
             std::vector<VariableDefExprAST *> members);
    virtual ~ClassAST();
    llvm::Type *                      Codegen();
    static ClassAST *                 ParseClass(CompileUnit *unit);
    std::vector<VariableDefExprAST *> members;
    std::string                       className;
};

#endif /* SRC_AST_CLASSAST_H_ */
