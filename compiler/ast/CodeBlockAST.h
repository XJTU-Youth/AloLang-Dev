/*
 * CodeBlockAST.h
 *
 *  Created on: Dec 27, 2020
 *      Author: zbc
 */

#ifndef COMPILER_AST_CODEBLOCKAST_H_
#define COMPILER_AST_CODEBLOCKAST_H_

#include "BaseAST.h"
#include "ExprAST.h"
#include "llvm/IR/Instructions.h"
#include <map>

class CodeBlockAST: public BaseAST {
public:
	CodeBlockAST(CompileUnit *unit, std::vector<ExprAST*> exprs,
			std::string name);
	virtual ~CodeBlockAST();
	static CodeBlockAST* ParseCodeBlock(CompileUnit *unit, std::string name);
	llvm::BasicBlock* Codegen();

	llvm::IRBuilder<> *builder;
	std::vector<ExprAST*> body;
	std::map<std::string, llvm::AllocaInst*> namedValues;//对类型的处理
	std::string name;
};

#endif /* COMPILER_AST_CODEBLOCKAST_H_ */
