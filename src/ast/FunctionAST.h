/*
 * FunctionAST.h
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#ifndef COMPILER_AST_FUNCTIONAST_H_
#define COMPILER_AST_FUNCTIONAST_H_

#include "BaseAST.h"
#include "CodeBlockAST.h"
#include "ExprAST.h"
#include "PrototypeAST.h"
#include <vector>

class FunctionAST : public BaseAST
{
  public:
    FunctionAST(CompileUnit *unit, PrototypeAST *proto, CodeBlockAST *body);
    virtual ~FunctionAST();
    llvm::Function *Codegen();
    std::string     getDemangledName();
    PrototypeAST *  proto;

    CodeBlockAST *      body;
    static FunctionAST *ParseFunction(CompileUnit *unit);
};

#endif /* COMPILER_AST_FUNCTIONAST_H_ */
