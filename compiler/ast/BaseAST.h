#ifndef COMPILER_AST_ASTBASE_H_
#define COMPILER_AST_ASTBASE_H_

#include <llvm/IR/Value.h>

class BaseAST {
public:
	BaseAST();
	virtual ~BaseAST();
	virtual llvm::Value *Codegen() = 0;
};

#endif /* COMPILER_AST_ASTBASE_H_ */
