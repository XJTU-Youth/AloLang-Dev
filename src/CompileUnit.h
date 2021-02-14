/*
 * CompileUnit.h
 *
 *  Created on: Dec 16, 2020
 *      Author: zbc
 */

#ifndef COMPILER_COMPILEUNIT_H_
#define COMPILER_COMPILEUNIT_H_

#include <string>
#include <sstream>
#include "Token.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <FlexLexer.h>

class CompileUnit {
public:
	CompileUnit(std::string name, std::string source);
	virtual ~CompileUnit();
	void compile();
	Token next_tok();
	void build();

	FlexLexer* lexer;

	std::string name;
	std::string source;
	std::istringstream sis;
	Token curTok;
	llvm::LLVMContext *context;
	llvm::Module *module;

};

#endif /* COMPILER_COMPILEUNIT_H_ */
