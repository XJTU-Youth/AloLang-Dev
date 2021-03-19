/*
 * KernelCompileExprAST.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: zbc
 */

#include "KernelCompileExprAST.h"
#include "TypeAST.h"

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
    std::string dname = "__alolang__inner_ipckernel_compile"; // todo:硬编码
    llvm::Function *CalleeF = unit->module->getFunction(dname);
    if (CalleeF == nullptr) {
        llvm::FunctionType *FT = llvm::FunctionType::get(
            llvm::Type::getVoidTy(*unit->context),
            std::vector<llvm::Type *>{
                llvm::IntegerType::get(*unit->context, 64),
                TypeAST(unit, "string").Codegen()},
            false);
        CalleeF = llvm::Function::Create(FT, llvm::GlobalValue::ExternalLinkage,
                                         dname, unit->module);
    }
    std::vector<llvm::Value *> args;
    llvm::Value *              kernel_addr =
        builder->CreatePtrToInt(kernelPointer->Codegen(builder)[0],
                                llvm::IntegerType::get(*unit->context, 64));
    args.push_back(kernel_addr);
    args.push_back(this->source->Codegen(builder)[0]);
    builder->CreateCall(CalleeF, args);

    return result;
}
