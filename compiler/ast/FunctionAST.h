/*
 * FunctionAST.h
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#ifndef COMPILER_AST_FUNCTIONAST_H_
#define COMPILER_AST_FUNCTIONAST_H_

#include "BaseAST.h"
#include "PrototypeAST.h"
#include <vector>
#include "ExprAST.h"

class FunctionAST: public BaseAST {
public:
	FunctionAST(CompileUnit* unit,PrototypeAST* proto,std::vector<ExprAST*>);
	virtual ~FunctionAST();
	llvm::Function *Codegen();
	PrototypeAST* proto;

	std::vector<ExprAST*> body;
	static FunctionAST* ParseFunction(CompileUnit* unit);

};

#endif /* COMPILER_AST_FUNCTIONAST_H_ */
