/*
 * CompileUnit.h
 *
 *  Created on: Dec 16, 2020
 *      Author: zbc
 */

#ifndef COMPILER_COMPILEUNIT_H_
#define COMPILER_COMPILEUNIT_H_

#include "Token.h"
#include <FlexLexer.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <sstream>
#include <string>

class CompileUnit
{
  public:
    CompileUnit(std::string name, std::string source);
    virtual ~CompileUnit();
    void  compile();
    Token next_tok();
    void  build();

    FlexLexer *                  lexer;
    Token                        curTok;
    std::string                  name;
    std::string                  source;
    std::istringstream           sis;
    llvm::LLVMContext *          context;
    llvm::Module *               module;
    std::vector<Token>           tokenList;
    std::vector<Token>::iterator icurTok;
};

#endif /* COMPILER_COMPILEUNIT_H_ */
