/*
 * CompileUnit.h
 *
 *  Created on: Dec 16, 2020
 *      Author: zbc
 */

#ifndef COMPILER_COMPILEUNIT_H_
#define COMPILER_COMPILEUNIT_H_

#include "Token.h"
#include "preprocessor.h"
#include <FlexLexer.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <sstream>
#include <string>

class TypeAST;
class FunctionAST;
class ExternAST;
class VariableDefExprAST;
class ClassAST;
class CompileUnit
{
  public:
    CompileUnit(std::string name, std::vector<Tline> lines);
    virtual ~CompileUnit();
    void  compile();
    Token next_tok();
    void  build();

    std::string                                 name;
    std::vector<Tline>                          srclines;
    llvm::LLVMContext *                         context;
    llvm::Module *                              module;
    std::vector<Token>                          tokenList;
    std::vector<Token>::iterator                icurTok;
    std::map<std::string, ClassAST *>           classes;
    std::vector<ClassAST *>                     classesO;
    std::map<std::string, VariableDefExprAST *> globalVariables;
    std::vector<VariableDefExprAST *>           globalVariablesO;
    std::map<std::string, FunctionAST *>        functions;
    std::map<std::string, ExternAST *>          externs;
    std::map<std::array<std::string, 3>, std::pair<llvm::Function *, TypeAST *>>
                                        binOperators; // LHS type,RHS type,binOP
    std::map<std::string, llvm::Type *> types;        // Codgen用
    std::map<std::string, std::pair<TypeAST *, llvm::Value *>>
        globalVariablesValue; // Codgen用
    // std::map<std::string, >
};

#endif /* COMPILER_COMPILEUNIT_H_ */
