#ifndef COMPILER_AST_ASTEXPR_H_
#define COMPILER_AST_ASTEXPR_H_

#include "BaseAST.h"

class ExprAST: public BaseAST {
public:
	ExprAST(CompileUnit *unit);
	virtual ~ExprAST();
	virtual llvm::Value* Codegen(llvm::IRBuilder<> *builder) =0;
	static ExprAST* ParseExpression(CompileUnit *unit);
	static ExprAST* ParsePrimary(CompileUnit *unit);
};

#endif /* COMPILER_AST_ASTEXPR_H_ */
