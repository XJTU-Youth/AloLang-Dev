/*
 * KernelCompileExprAST.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: zbc
 */

#include "KernelCompileExprAST.h"

KernelCompileExprAST::KernelCompileExprAST(CompileUnit * unit,
                                           CodeBlockAST *codeblock,
                                           ExprAST *     kernelPointer,
                                           ExprAST *     source)
    : ExprAST(unit)
{
    this->codeblock     = codeblock;
    this->kernelPointer = kernelPointer;
    this->source        = source;
}

KernelCompileExprAST::~KernelCompileExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *>
KernelCompileExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> result;
    return result;
}
