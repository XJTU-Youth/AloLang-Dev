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
    TypeAST(CompileUnit *unit, std::string baseClass,
            std::vector<TypeAST *> genericTypes = std::vector<TypeAST *>());
    virtual ~TypeAST();
    static TypeAST *       ParseType(CompileUnit *unit);
    llvm::Type *           Codegen();
    std::string            name;
    std::string            baseClass;
    std::vector<TypeAST *> innerType;
    std::vector<TypeAST *> genericTypes;
};

#endif /* SRC_AST_TYPEAST_H_ */
