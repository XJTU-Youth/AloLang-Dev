/*
 * FunctionAST.h
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#ifndef COMPILER_AST_FUNCTIONAST_H_
#define COMPILER_AST_FUNCTIONAST_H_

#include "BaseAST.h"

class FunctionAST: public BaseAST {
public:
	FunctionAST();
	virtual ~FunctionAST();
	llvm::Function *Codegen();
	static FunctionAST* ParseDefinition();
};

#endif /* COMPILER_AST_FUNCTIONAST_H_ */
