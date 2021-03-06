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
             std::map<std::string, VariableDefExprAST *> members,
             std::map<std::string, FunctionAST *>        functions,
             std::vector<std::string>                    genericTypes);
    virtual ~ClassAST();
    llvm::Type *Codegen(std::vector<TypeAST *> genericTypes);
    TypeAST *getRealType(TypeAST *type, std::vector<TypeAST *> igenericTypes);
    std::string getRealName(std::vector<TypeAST *> igenericTypes);

    std::string getRealNameForMangle(std::vector<TypeAST *> igenericTypes);

    static ClassAST *                           ParseClass(CompileUnit *unit);
    std::map<std::string, VariableDefExprAST *> members;
    std::map<std::string, FunctionAST *>        functions;
    std::vector<std::string>                    genericTypes;
    std::string                                 className;
};

#endif /* SRC_AST_CLASSAST_H_ */
