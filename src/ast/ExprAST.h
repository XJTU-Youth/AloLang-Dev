#ifndef COMPILER_AST_ASTEXPR_H_
#define COMPILER_AST_ASTEXPR_H_

#include "BaseAST.h"

class CodeBlockAST;
class ExprAST : public BaseAST
{
  public:
    ExprAST(CompileUnit *unit);
    virtual ~ExprAST();
    virtual std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder) = 0;
    static ExprAST *ParseExpression(CompileUnit *unit, CodeBlockAST *codeblock,
                                    bool root);
    static ExprAST *ParsePrimary(CompileUnit *unit, CodeBlockAST *codeblock);
    std::vector<TypeAST *> type;
    ExprAST *              subExpr;
};

#endif /* COMPILER_AST_ASTEXPR_H_ */
