/*
 * KernelCallExprAST.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: zbc
 */

#include "KernelCallExprAST.h"

KernelCallExprAST::KernelCallExprAST(CompileUnit *unit, ExprAST *kernel)
    : ExprAST(unit)
{
    this->kernel = kernel;
}

KernelCallExprAST::~KernelCallExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *>
KernelCallExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> result;
    std::string     dname = "__alolang__inner_ipckernel_call"; // todo:硬编码
    llvm::Function *CalleeF = unit->module->getFunction(dname);
    if (CalleeF == nullptr) {
        llvm::FunctionType *FT =
            llvm::FunctionType::get(llvm::Type::getVoidTy(*unit->context),
                                    std::vector<llvm::Type *>{}, false);
        CalleeF = llvm::Function::Create(FT, llvm::GlobalValue::ExternalLinkage,
                                         dname, unit->module);
    }
    std::vector<llvm::Value *> args;
    builder->CreateCall(CalleeF, args);

    return result;
}
