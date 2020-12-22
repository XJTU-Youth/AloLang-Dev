/*
 * NumberExprAST.h
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#ifndef COMPILER_AST_INTEXPRAST_H_
#define COMPILER_AST_INTEXPRAST_H_

#include "ExprAST.h"

class NumberExprAST: public ExprAST {
public:
	NumberExprAST(CompileUnit* unit);
	virtual ~NumberExprAST();
	int val;
};

#endif /* COMPILER_AST_INTEXPRAST_H_ */
