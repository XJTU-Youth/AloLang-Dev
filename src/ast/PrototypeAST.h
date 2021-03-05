/*
 * PrototypeAST.h
 *
 *  Created on: Dec 21, 2020
 *      Author: zbc
 */

#ifndef COMPILER_AST_PROTOTYPEAST_H_
#define COMPILER_AST_PROTOTYPEAST_H_

#include "BaseAST.h"

class PrototypeAST : public BaseAST
{
  public:
    PrototypeAST(CompileUnit *unit, const std::string &name,
                 const std::vector<std::pair<TypeAST *, std::string>> &args,
                 const std::vector<TypeAST *> &returnTypes,
                 ClassAST *                    parentClass);
    virtual ~PrototypeAST();
    llvm::Function *
    Codegen(std::vector<TypeAST *> igenericTypes = std::vector<TypeAST *>());
    static PrototypeAST *ParsePrototype(CompileUnit *unit, bool hasBody,
                                        ClassAST *parentClass = nullptr);
    std::vector<std::pair<TypeAST *, std::string>> args;

    std::string demangledName;

    std::vector<TypeAST *> returnTypes;
    std::string            name;
    bool                   returnDirectly; //直接返回
    ClassAST *             parentClass;
};

#endif /* COMPILER_AST_PROTOTYPEAST_H_ */
