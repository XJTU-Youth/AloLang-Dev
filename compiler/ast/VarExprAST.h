/*
 * VarExprAST.h
 *
 *  Created on: Jan 23, 2021
 *      Author: zbc
 */

#ifndef COMPILER_AST_VAREXPRAST_H_
#define COMPILER_AST_VAREXPRAST_H_
#include "ExprAST.h"

class VarExprAST: public ExprAST {
public:
	VarExprAST(CompileUnit *unit);
	virtual ~VarExprAST();
};

#endif /* COMPILER_AST_VAREXPRAST_H_ */
