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
    std::vector<llvm::Value *>         CodegenChain(llvm::IRBuilder<> *builder);
    virtual llvm::Value *              getAlloca(llvm::IRBuilder<> *builder);
    static ExprAST *ParseExpression(CompileUnit *unit, CodeBlockAST *codeblock,
                                    bool root);
    static ExprAST *ParsePrimary(CompileUnit *unit, CodeBlockAST *codeblock,
                                 bool root = false);

    std::vector<TypeAST *> type;
    ExprAST *              subExpr;
};

static ExprAST *ParseBinOpRHS(CompileUnit *unit, CodeBlockAST *codeblock,
                              int ExprPrec, ExprAST *LHS);
#endif /* COMPILER_AST_ASTEXPR_H_ */
