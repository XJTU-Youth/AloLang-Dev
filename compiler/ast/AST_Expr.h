#ifndef COMPILER_AST_ASTEXPR_H_
#define COMPILER_AST_ASTEXPR_H_

#include "AST_Base.h"

class AST_Expr: public AST_Base {
public:
	AST_Expr();
	virtual ~AST_Expr();
};

#endif /* COMPILER_AST_ASTEXPR_H_ */
