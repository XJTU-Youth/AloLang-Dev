/*
 * FunctionAST.cpp
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#include "FunctionAST.h"
#include "../CompileError.hpp"
#include "ClassAST.h"
#include "CodeBlockAST.h"
#include "PrototypeAST.h"
#include "TypeAST.h"
#include "VariableDefExprAST.h"
#include "VariableExprAST.h"
#include <iomanip>
#include <iostream>
#include <llvm/IR/IRBuilder.h>

FunctionAST::FunctionAST(CompileUnit *unit, PrototypeAST *proto,
                         CodeBlockAST *body, ClassAST *parentClass)
    : BaseAST(unit)
{
    this->proto       = proto;
    this->body        = body;
    this->parentClass = parentClass;
}

FunctionAST::~FunctionAST()
{
    // TODO Auto-generated destructor stub
}

void FunctionAST::processInnerFunction(llvm::Function *func)
{
    llvm::IRBuilder<> *builder = new llvm::IRBuilder<>(*unit->context);
    llvm::BasicBlock * bb =
        llvm::BasicBlock::Create(*unit->context, "entry", func);
    builder->SetInsertPoint(bb);
    std::vector<llvm::Value *> returnValue = std::vector<llvm::Value *>();
    llvm::IRBuilder<>          sBuilder(&func->getEntryBlock(),
                               func->getEntryBlock().begin());

    llvm::StructType *sType  = (llvm::StructType *)func->getReturnType();
    llvm::AllocaInst *alloca = sBuilder.CreateAlloca(sType);

    if (proto->name == "__alolang_inner_load") {
        llvm::IntegerType *itype = llvm::IntegerType::get(*unit->context, 32);
        llvm::Type *       classType =
            ((llvm::PointerType *)func->getArg(0)->getType())->getElementType();
        llvm::Type * realType  = parentClass->igenericTypes[0]->Codegen();
        llvm::Value *thisValue = func->getArg(0);
        llvm::Value *pointer   = builder->CreateGEP(
            classType, thisValue,
            std::vector<llvm::Value *>{llvm::ConstantInt::get(itype, 0, true),
                                       llvm::ConstantInt::get(itype, 0, true)});
        pointer = builder->CreateLoad(pointer);
        pointer = builder->CreateIntToPtr(pointer,
                                          llvm::PointerType::get(realType, 0));
        returnValue.push_back(pointer);
    } else if (proto->name == "__alolang_inner_toObj") {
        llvm::IntegerType *itype = llvm::IntegerType::get(*unit->context, 32);
        llvm::Type *       classType =
            ((llvm::PointerType *)func->getArg(0)->getType())->getElementType();

        llvm::Type * realType = parentClass->igenericTypes[0]->Codegen();
        llvm::Value *pointer  = builder->CreateGEP(
            classType, func->getArg(0),
            std::vector<llvm::Value *>{llvm::ConstantInt::get(itype, 0, true),
                                       llvm::ConstantInt::get(itype, 0, true)});
        llvm::Value *addr = builder->CreatePtrToInt(
            func->getArg(1), llvm::IntegerType::get(*unit->context, 64));
        builder->CreateStore(addr, pointer);

    } else {
        CompileError e("No inner function:" + proto->name);
        throw e;
    }
    for (int i = 0; i < returnValue.size(); i++) {
        llvm::IntegerType *type = llvm::IntegerType::get(*unit->context, 32);
        llvm::ConstantInt *res  = llvm::ConstantInt::get(type, i, true);

        llvm::Value *member_ptr = builder->CreateGEP(
            sType, alloca, {llvm::ConstantInt::get(type, 0, true), res});
        builder->CreateStore(returnValue[i], member_ptr);
        // builder->CreateLoad(member_ptr);
    }

    for (int i = 0; i < returnValue.size(); i++) {
        llvm::IntegerType *type = llvm::IntegerType::get(*unit->context, 32);
        llvm::ConstantInt *res  = llvm::ConstantInt::get(type, i, true);

        llvm::Value *member_ptr = builder->CreateGEP(
            sType, alloca, {llvm::ConstantInt::get(type, 0, true), res});
        builder->CreateStore(returnValue[i], member_ptr);
        // builder->CreateLoad(member_ptr);
    }
    builder->CreateRet(builder->CreateLoad(alloca));
}

llvm::Function *FunctionAST::Codegen(std::vector<TypeAST *> igenericTypes)
{
    this->igenericTypes  = igenericTypes;
    llvm::Function *func = proto->Codegen(igenericTypes);
    unit->globalFunctions.insert(
        std::pair<std::string, std::pair<PrototypeAST *, llvm::Function *>>(
            func->getName(),
            std::pair<PrototypeAST *, llvm::Function *>(proto, func)));
    if (proto->name.substr(0, 16) == "__alolang_inner_") {
        processInnerFunction(func);
    } else {
        llvm::BasicBlock *bb = body->Codegen(func);
    }
    // func->getBasicBlockList().push_back(bb);

    return func;
}

FunctionAST *FunctionAST::ParseFunction(CompileUnit *unit,
                                        ClassAST *   parentClass)
{
    PrototypeAST *protoType =
        PrototypeAST::ParsePrototype(unit, true, parentClass);
    if (parentClass != nullptr) {
        std::vector<TypeAST *> genericTypes;
        for (std::string gType : parentClass->genericTypes) {
            genericTypes.push_back(new TypeAST(unit, gType));
        }
        protoType->args.insert(
            protoType->args.begin(),
            std::pair<TypeAST *, std::string>(
                new TypeAST(unit, new TypeAST(unit, parentClass->className,
                                              genericTypes, parentClass)),
                "this"));
    }
    std::cout << std::left << std::setw(35)
              << "Function definition found:" << protoType->name << std::endl;
    std::vector<VariableDefExprAST *> args;

    for (unsigned int i = 0; i < protoType->args.size(); i++) {
        std::pair<TypeAST *, std::string> arg = protoType->args[i];
        args.push_back(new VariableDefExprAST(unit, nullptr, arg.second,
                                              arg.first, nullptr, i));
    }
    FunctionAST *result =
        new FunctionAST(unit, protoType, nullptr, parentClass);

    CodeBlockAST *body =
        CodeBlockAST::ParseCodeBlock(unit, "entry", result, nullptr, args);
    result->body = body;

    return result;
}
