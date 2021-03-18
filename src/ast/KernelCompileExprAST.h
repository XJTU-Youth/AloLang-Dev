/*
 * KernelCompileExprAST.h
 *
 *  Created on: Mar 18, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_KERNELCOMPILEEXPRAST_H_
#define SRC_AST_KERNELCOMPILEEXPRAST_H_

#include "CodeBlockAST.h"
#include "ExprAST.h"

class KernelCompileExprAST : public ExprAST
{
  public:
    KernelCompileExprAST(CompileUnit *unit, CodeBlockAST *codeblock,
                         ExprAST *kernelPointer, ExprAST *source);
    virtual ~KernelCompileExprAST();
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);

    ExprAST *     kernelPointer;
    ExprAST *     source;
    CodeBlockAST *codeblock;
};

#endif /* SRC_AST_KERNELCOMPILEEXPRAST_H_ */
