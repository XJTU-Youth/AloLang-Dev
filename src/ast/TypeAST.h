/*
 * TypeAST.h
 *
 *  Created on: Feb 16, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_TYPEAST_H_
#define SRC_AST_TYPEAST_H_

#include "BaseAST.h"

class TypeAST : public BaseAST
{
  public:
    TypeAST(CompileUnit *unit, std::string name);
    virtual ~TypeAST();
    llvm::Type *           Codegen();
    std::string            name;
    std::vector<TypeAST *> innerType;
};

#endif /* SRC_AST_TYPEAST_H_ */
