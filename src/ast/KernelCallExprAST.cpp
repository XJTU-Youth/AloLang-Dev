/*
 * KernelCallExprAST.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: zbc
 */

#include "KernelCallExprAST.h"
#include "CodeBlockAST.h"
#include "IntExprAST.h"
#include "StringExprAST.h"
#include "TypeAST.h"

KernelCallExprAST::KernelCallExprAST(CompileUnit *unit, CodeBlockAST *codeblock,
                                     ExprAST *kernel)
    : ExprAST(unit)
{
    this->kernel    = kernel;
    this->codeblock = codeblock;
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
        llvm::FunctionType *FT = llvm::FunctionType::get(
            llvm::Type::getVoidTy(*unit->context),
            std::vector<llvm::Type *>{
                llvm::IntegerType::get(*unit->context, 64),
                llvm::IntegerType::get(*unit->context, 64),
                llvm::IntegerType::get(*unit->context, 64)},
            false);
        CalleeF = llvm::Function::Create(FT, llvm::GlobalValue::ExternalLinkage,
                                         dname, unit->module);
    }
    std::map<std::string, llvm::Value *> passedVariable;
    std::map<std::string, std::pair<TypeAST *, llvm::Value *>>::iterator iter;
    CodeBlockAST *curBlock = this->codeblock;
    while (curBlock != nullptr) {
        for (iter = curBlock->namedValues.begin();
             iter != curBlock->namedValues.end(); iter++) {
            if (iter->second.first->baseClass == "int") {
                passedVariable.insert(std::pair<std::string, llvm::Value *>(
                    iter->first, iter->second.second));
            }
        }
        curBlock = curBlock->parent;
    }
    llvm::Type *sType = llvm::ArrayType::get(TypeAST(unit, "VarPair").Codegen(),
                                             passedVariable.size());
    llvm::Function *function = builder->GetInsertBlock()->getParent();

    llvm::IRBuilder<> sBuilder(&function->getEntryBlock(),
                               function->getEntryBlock().begin());

    llvm::AllocaInst * vararray_alloca = sBuilder.CreateAlloca(sType);
    llvm::IntegerType *itype = llvm::IntegerType::get(*unit->context, 32);

    std::map<std::string, llvm::Value *>::iterator piter;
    int                                            cnt = 0;

    for (piter = passedVariable.begin(); piter != passedVariable.end();
         piter++) {
        //存入Name
        llvm::Value *pointer = builder->CreateGEP(
            sType, vararray_alloca,
            std::vector<llvm::Value *>{llvm::ConstantInt::get(itype, 0, true),
                                       llvm::ConstantInt::get(itype, cnt, true),
                                       llvm::ConstantInt::get(itype, 1, true)});
        builder->CreateStore(
            StringExprAST(unit, piter->first).Codegen(builder)[0], pointer);
        //存入value
        pointer = builder->CreateGEP(
            sType, vararray_alloca,
            std::vector<llvm::Value *>{llvm::ConstantInt::get(itype, 0, true),
                                       llvm::ConstantInt::get(itype, cnt, true),
                                       llvm::ConstantInt::get(itype, 0, true)});
        llvm::Value *var_addr = builder->CreatePtrToInt(
            piter->second, llvm::IntegerType::get(*unit->context, 64));

        builder->CreateStore(var_addr, pointer);
        cnt++;
    }

    std::vector<llvm::Value *> args;
    llvm::Value *              kernel_addr =
        builder->CreatePtrToInt(kernel->Codegen(builder)[0],
                                llvm::IntegerType::get(*unit->context, 64));
    args.push_back(kernel_addr);
    args.push_back(IntExprAST(unit, passedVariable.size()).Codegen(builder)[0]);
    args.push_back(builder->CreatePtrToInt(
        vararray_alloca, llvm::IntegerType::get(*unit->context, 64)));
    builder->CreateCall(CalleeF, args);

    return result;
}
