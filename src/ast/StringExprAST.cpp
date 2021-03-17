/*
 * StringExprAST.cpp
 *
 *  Created on: Mar 14, 2021
 *      Author: zbc
 */

#include "StringExprAST.h"
#include "../CompileError.hpp"
#include "CallExprAST.h"
#include "IntExprAST.h"
#include "TypeAST.h"

StringExprAST::StringExprAST(CompileUnit *unit, const std::string &str)
    : ExprAST(unit)
{
    this->str = str;
}

StringExprAST::~StringExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> StringExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    type.clear();

    /*llvm::Constant *           strArray =
        llvm::ConstantDataArray::getString(unit->module->getContext(), str);*/
    llvm::Value *strArray = builder->CreateGlobalString(str);

    llvm::Function *function = builder->GetInsertBlock()->getParent();

    llvm::IRBuilder<> sBuilder(&function->getEntryBlock(),
                               function->getEntryBlock().begin());

    llvm::StructType *sType =
        (llvm::StructType *)TypeAST(
            unit, "array", std::vector<TypeAST *>{new TypeAST(unit, "char")})
            .Codegen();
    llvm::AllocaInst *array_alloca = sBuilder.CreateAlloca(sType);
    llvm::AllocaInst *result_alloca =
        sBuilder.CreateAlloca(TypeAST(unit, "string").Codegen());
    std::string dname =
        "_alolang_C5arrayE4initP5array4chare3inte"; // todo:硬编码
    llvm::Function *CalleeF = unit->module->getFunction(dname);
    if (CalleeF == 0) {
        CompileError e("Function " + dname +
                       " not found in LLVM IR when building string");
        throw e;
    }
    std::vector<llvm::Value *> args;
    args.push_back(array_alloca);
    args.push_back((new IntExprAST(unit, str.length()))->Codegen(builder)[0]);
    builder->CreateCall(CalleeF, args);
    llvm::IntegerType *itype   = llvm::IntegerType::get(*unit->context, 32);
    llvm::IntegerType *itype64 = llvm::IntegerType::get(*unit->context, 64);

    std::vector<TypeAST *> genericTypes = std::vector<TypeAST *>();
    genericTypes.push_back(new TypeAST(unit, "char"));
    llvm::Value *startPointer = builder->CreateLoad(builder->CreateGEP(
        sType, array_alloca,
        std::vector<llvm::Value *>{llvm::ConstantInt::get(itype, 0, true),
                                   llvm::ConstantInt::get(itype, 0, true),
                                   llvm::ConstantInt::get(itype, 0, true)}));
    llvm::Value *strValue     = builder->CreateGEP(
        llvm::ArrayType::get(llvm::IntegerType::get(*unit->context, 8),
                             str.length() + 1),
        strArray,
        std::vector<llvm::Value *>{llvm::ConstantInt::get(itype64, 0, true),
                                   llvm::ConstantInt::get(itype64, 0, true)});
    // llvm::Value *strValue    = builder->CreateGlobalString(str);
    dname                    = "__alolang_inner_load_string"; // todo:硬编码
    llvm::Function *CalleeF2 = unit->module->getFunction(dname);
    if (CalleeF2 == nullptr) {
        llvm::FunctionType *FT = llvm::FunctionType::get(
            TypeAST(unit, "int").Codegen(),
            std::vector<llvm::Type *>{
                llvm::PointerType::get(
                    llvm::IntegerType::get(*unit->context, 8), 0),
                llvm::IntegerType::get(*unit->context, 64)},
            false);
        CalleeF2 =
            llvm::Function::Create(FT, llvm::GlobalValue::ExternalLinkage,
                                   "__alolang_inner_load_string", unit->module);
    }
    std::vector<llvm::Value *> args2;
    args2.push_back(strValue);
    // args2.push_back(llvm::ConstantInt::get(itype64, 0, true));
    args2.push_back(startPointer);
    llvm::Value *ret = builder->CreateCall(CalleeF2, args2);
    builder->CreateStore(
        ret, builder->CreateGEP(sType, array_alloca,
                                std::vector<llvm::Value *>{
                                    llvm::ConstantInt::get(itype, 0, true),
                                    llvm::ConstantInt::get(itype, 1, true)}));
    //制作结果
    this->type.push_back(new TypeAST(unit, "string"));
    // todo:待优化
    std::vector<llvm::Value *> result;
    builder->CreateStore(
        builder->CreateLoad(array_alloca),
        builder->CreateGEP(TypeAST(unit, "string").Codegen(), result_alloca,
                           std::vector<llvm::Value *>{
                               llvm::ConstantInt::get(itype, 0, true),
                               llvm::ConstantInt::get(itype, 0, true)}));
    llvm::Value *resultValue = builder->CreateLoad(result_alloca);
    result.push_back(resultValue);
    return result;
}
