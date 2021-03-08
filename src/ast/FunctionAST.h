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
    FunctionAST(CompileUnit *unit, PrototypeAST *proto, CodeBlockAST *body,
                ClassAST *parentClass = nullptr);
    virtual ~FunctionAST();
    llvm::Function *
    Codegen(std::vector<TypeAST *> igenericTypes = std::vector<TypeAST *>());
    void processInnerFunction(llvm::Function *func);

    PrototypeAST *proto;
    ClassAST *    parentClass;

    CodeBlockAST *         body;
    std::vector<TypeAST *> igenericTypes;
    static FunctionAST *   ParseFunction(CompileUnit *unit,
                                         ClassAST *   parentClass = nullptr);
};

#endif /* COMPILER_AST_FUNCTIONAST_H_ */
