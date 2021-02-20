/*
 * ExternAST.h
 *
 *  Created on: Dec 23, 2020
 *      Author: zbc
 */

#ifndef COMPILER_AST_EXTERNAST_H_
#define COMPILER_AST_EXTERNAST_H_

#include "BaseAST.h"
#include "PrototypeAST.h"

class ExternAST : public BaseAST
{
  public:
    ExternAST(CompileUnit *unit, PrototypeAST *prototype);
    virtual ~ExternAST();
    static ExternAST *ParseExtern(CompileUnit *unit);
    llvm::Function *  Codegen();
    PrototypeAST *    proto;
    std::string       getDemangledName();
};

#endif /* COMPILER_AST_EXTERNAST_H_ */
