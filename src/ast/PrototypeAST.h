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
                 const std::vector<std::pair<std::string, std::string>> &args,
                 const std::vector<std::string> &returnTypes);
    virtual ~PrototypeAST();
    llvm::Function *     Codegen();
    static PrototypeAST *ParsePrototype(CompileUnit *unit, bool hasBody);
    std::vector<std::pair<std::string, std::string>> args;
    std::vector<std::string>                         returnTypes;
    std::string                                      name;
    bool returnDirectly; //直接返回
};

#endif /* COMPILER_AST_PROTOTYPEAST_H_ */
