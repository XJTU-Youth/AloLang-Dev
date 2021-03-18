/*
 * KernelCallExprAST.h
 *
 *  Created on: Mar 18, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_KERNELCALLEXPRAST_H_
#define SRC_AST_KERNELCALLEXPRAST_H_

#include "ExprAST.h"

class KernelCallExprAST : public ExprAST
{
  public:
    KernelCallExprAST(CompileUnit *unit, ExprAST *kernel);
    virtual ~KernelCallExprAST();
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);

    ExprAST *kernel;
};

#endif /* SRC_AST_KERNELCALLEXPRAST_H_ */
