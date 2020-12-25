/*
 * PrototypeAST.h
 *
 *  Created on: Dec 21, 2020
 *      Author: zbc
 */

#ifndef COMPILER_AST_PROTOTYPEAST_H_
#define COMPILER_AST_PROTOTYPEAST_H_

#include "BaseAST.h"

class PrototypeAST: public BaseAST {
public:
	PrototypeAST(CompileUnit *unit, const std::string &name,
			const std::vector<std::pair<std::string, std::string>> &args);
	virtual ~PrototypeAST();
	llvm::Function* Codegen();
	static PrototypeAST* ParsePrototype(CompileUnit *unit, bool hasBody);
	std::vector<std::pair<std::string, std::string>> args;
	std::string name;
};

#endif /* COMPILER_AST_PROTOTYPEAST_H_ */
