/*
 * ClassAST.h
 *
 *  Created on: Feb 22, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_CLASSAST_H_
#define SRC_AST_CLASSAST_H_

#include "BaseAST.h"

class ClassAST : public BaseAST
{
  public:
    ClassAST(CompileUnit *unit);
    virtual ~ClassAST();
    llvm::Type *     Codegen();
    static ClassAST *ParseClass(CompileUnit *unit);
};

#endif /* SRC_AST_CLASSAST_H_ */
