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
    TypeAST(CompileUnit *unit, TypeAST *pointee);
    virtual ~TypeAST();
    static TypeAST *ParseType(CompileUnit *unit);
    void            initName();

    llvm::Type *           Codegen();
    std::string            getMangleName();
    std::string            name;
    std::string            baseClass;
    std::vector<TypeAST *> innerType;
    std::vector<TypeAST *> genericTypes;
    TypeAST *              pointee; //指向的类型
};

#endif /* SRC_AST_TYPEAST_H_ */
