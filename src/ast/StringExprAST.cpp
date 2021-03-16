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
    this->type.push_back(new TypeAST(unit, "string"));
    std::vector<llvm::Value *> result;
    llvm::Constant *           const_array_4 =
        llvm::ConstantDataArray::getString(unit->module->getContext(), str);
    llvm::Function *function = builder->GetInsertBlock()->getParent();

    llvm::IRBuilder<> sBuilder(&function->getEntryBlock(),
                               function->getEntryBlock().begin());

    llvm::StructType *sType =
        (llvm::StructType *)(new TypeAST(unit, "array<char>"))->Codegen();
    llvm::AllocaInst *alloca = sBuilder.CreateAlloca(sType);
    std::string       dname =
        "_alolang_C5arrayE4initP5array4chare3inte"; // todo:硬编码
    llvm::Function *CalleeF = unit->module->getFunction(dname);
    if (CalleeF == 0) {
        CompileError e("Function " + dname +
                       " not found in LLVM IR when building string");
        throw e;
    }
    std::vector<llvm::Value *> args;
    args.push_back(alloca);
    args.push_back((new IntExprAST(unit, str.length()))->Codegen(builder)[0]);
    builder->CreateCall(CalleeF, args);

    dname   = "_alolang_C5arrayE4initP5array4chare3inte"; // todo:硬编码
    CalleeF = unit->module->getFunction(dname);
    if (CalleeF == 0) {
        CompileError e("Function " + dname +
                       " not found in LLVM IR when building string");
        throw e;
    }
    args.clear();
    args.push_back(alloca);
    args.push_back((new IntExprAST(unit, str.length()))->Codegen(builder)[0]);
    llvm::Value *ret = builder->CreateCall(CalleeF, args);
    CompileError e("字符串字面值未实现");
    throw e;
    return result;
}
