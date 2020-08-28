#ifndef COMPILER_AST_ASTEXPR_H_
#define COMPILER_AST_ASTEXPR_H_

#include "BaseAST.h"

class ExprAST: public BaseAST {
public:
	ExprAST();
	virtual ~ExprAST();
	virtual llvm::Value *Codegen() = 0;
};

#endif /* COMPILER_AST_ASTEXPR_H_ */
