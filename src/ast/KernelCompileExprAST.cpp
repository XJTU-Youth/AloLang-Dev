/*
 * KernelCompileExprAST.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: zbc
 */

#include "KernelCompileExprAST.h"
#include "IntExprAST.h"
#include "StringExprAST.h"
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
    std::vector<llvm::Value *>           result;
    std::map<std::string, llvm::Value *> passedVariable;
    std::map<std::string, std::pair<TypeAST *, llvm::Value *>>::iterator iter;
    llvm::IntegerType *itype = llvm::IntegerType::get(*unit->context, 32);

    for (iter = this->codeblock->namedValues.begin();
         iter != this->codeblock->namedValues.end(); iter++) {
        if (iter->second.first->baseClass == "int") {
            passedVariable.insert(std::pair<std::string, llvm::Value *>(
                iter->first, iter->second.second));
        }
    }

    std::string dname = "__alolang__inner_ipckernel_compile"; // todo:硬编码
    llvm::Type *sType = llvm::ArrayType::get(TypeAST(unit, "string").Codegen(),
                                             passedVariable.size());

    llvm::Function *CalleeF = unit->module->getFunction(dname);
    if (CalleeF == nullptr) {
        llvm::FunctionType *FT = llvm::FunctionType::get(
            llvm::Type::getVoidTy(*unit->context),
            std::vector<llvm::Type *>{
                llvm::IntegerType::get(*unit->context, 64),
                llvm::IntegerType::get(*unit->context, 64),
                llvm::IntegerType::get(*unit->context, 64),
                TypeAST(unit, "string").Codegen()},
            false);
        CalleeF = llvm::Function::Create(FT, llvm::GlobalValue::ExternalLinkage,
                                         dname, unit->module);
    }
    llvm::Value *kernel_addr =
        builder->CreatePtrToInt(kernelPointer->Codegen(builder)[0],
                                llvm::IntegerType::get(*unit->context, 64));

    llvm::Function *function = builder->GetInsertBlock()->getParent();

    llvm::IRBuilder<> sBuilder(&function->getEntryBlock(),
                               function->getEntryBlock().begin());

    llvm::AllocaInst *vararray_alloca = sBuilder.CreateAlloca(sType);
    std::map<std::string, llvm::Value *>::iterator piter;
    int                                            cnt = 0;
    for (piter = passedVariable.begin(); piter != passedVariable.end();
         piter++) {
        //存入Name
        llvm::Value *pointer =
            builder->CreateGEP(sType, vararray_alloca,
                               std::vector<llvm::Value *>{
                                   llvm::ConstantInt::get(itype, 0, true),
                                   llvm::ConstantInt::get(itype, cnt, true)});
        builder->CreateStore(
            StringExprAST(unit, piter->first).Codegen(builder)[0], pointer);
        //存入value
        /*pointer = builder->CreateGEP(
            sType, vararray_alloca,
            std::vector<llvm::Value *>{llvm::ConstantInt::get(itype, 0, true),
                                       llvm::ConstantInt::get(itype, cnt, true),
                                       llvm::ConstantInt::get(itype, 1, true)});
        llvm::Value *var_addr = builder->CreatePtrToInt(
            piter->second, llvm::IntegerType::get(*unit->context, 64));

        builder->CreateStore(var_addr, pointer);*/
        cnt++;
    }

    std::vector<llvm::Value *> args;
    args.push_back(kernel_addr);
    args.push_back(IntExprAST(unit, passedVariable.size()).Codegen(builder)[0]);
    args.push_back(builder->CreatePtrToInt(
        vararray_alloca, llvm::IntegerType::get(*unit->context, 64)));
    args.push_back(this->source->Codegen(builder)[0]);
    builder->CreateCall(CalleeF, args);

    return result;
}
