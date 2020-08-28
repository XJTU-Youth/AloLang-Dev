/*
 * VariableExprAST.h
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#ifndef COMPILER_AST_VARIABLEEXPRAST_H_
#define COMPILER_AST_VARIABLEEXPRAST_H_

#include "ExprAST.h"

class VariableExprAST: public ExprAST {
public:
	VariableExprAST();
	virtual ~VariableExprAST();
	virtual llvm::Value *Codegen();
};

#endif /* COMPILER_AST_VARIABLEEXPRAST_H_ */
