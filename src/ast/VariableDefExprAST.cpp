/*
 * VariableDefExprAST.cpp
 *
 *  Created on: Jan 23, 2021
 *      Author: zbc
 */

#include "VariableDefExprAST.h"

#include "../CompileError.hpp"
#include "CodeBlockAST.h"
#include "IntExprAST.h"
#include "TypeAST.h"
#include <iostream>
#include <map>

VariableDefExprAST::VariableDefExprAST(CompileUnit *      unit,
                                       CodeBlockAST *     codeblock,
                                       const std::string &idName, TypeAST *type,
                                       ExprAST *initValue, int argID)
    : ExprAST(unit)
{
    this->codeblock    = codeblock;
    this->idName       = idName;
    this->alloca       = nullptr;
    this->initValue    = initValue;
    this->argID        = argID;
    this->variableType = type;
}

VariableDefExprAST::~VariableDefExprAST()
{
    // TODO Auto-generated destructor stub
}

static llvm::AllocaInst *CreateEntryBlockAlloca(CompileUnit *      unit,
                                                llvm::Function *   function,
                                                const std::string &VarName,
                                                TypeAST *          typeAST)
{
    llvm::IRBuilder<> builder(&function->getEntryBlock(),
                              function->getEntryBlock().begin());
    return builder.CreateAlloca(typeAST->Codegen(), 0, VarName.c_str());
}

std::vector<llvm::Value *>
VariableDefExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    if (codeblock == nullptr) {
        llvm::GlobalVariable *gVar = new llvm::GlobalVariable(
            *unit->module, variableType->Codegen(), false,
            llvm::GlobalValue::ExternalLinkage, nullptr, idName);
        // todo:初始填0
        if (variableType->name == "int") {
            llvm::IntegerType *itype =
                llvm::IntegerType::get(*unit->context, 64);
            llvm::ConstantInt *res = llvm::ConstantInt::get(itype, 0, true);
            gVar->setInitializer(res);
        } else if (variableType->name == "double") {
            llvm::Type *    ftype = llvm::Type::getDoubleTy(*unit->context);
            llvm::Constant *res   = llvm::ConstantFP::get(ftype, 0);
            gVar->setInitializer(res);
        } else if (variableType->name == "bool") {
            llvm::IntegerType *itype =
                llvm::IntegerType::get(*unit->context, 1);
            llvm::ConstantInt *res = llvm::ConstantInt::get(itype, 0, true);
            gVar->setInitializer(res);
        }
        unit->globalVariablesValue.insert(
            std::pair<std::string, std::pair<TypeAST *, llvm::Value *>>(
                idName,
                std::pair<TypeAST *, llvm::Value *>(variableType, gVar)));
        //全局变量
    } else {
        //局部变量
        llvm::BasicBlock *insertBlock = builder->GetInsertBlock();
        llvm::Function *  function    = insertBlock->getParent();
        alloca = CreateEntryBlockAlloca(unit, function, idName, variableType);
        if (argID != -1) {
            builder->CreateStore(function->getArg(argID), alloca);
        }
        if (initValue != nullptr) {
            std::vector<llvm::Value *> ivalues = initValue->Codegen(builder);
            if (ivalues.size() != 1) {
                CompileError e("Multi/Void type in init found.");
                throw e;
            }
            builder->CreateStore(ivalues[0], alloca);
        }
        codeblock->namedValues.insert(
            std::pair<std::string, std::pair<TypeAST *, llvm::AllocaInst *>>(
                idName, std::pair<TypeAST *, llvm::AllocaInst *>(variableType,
                                                                 alloca)));
    }
    return std::vector<llvm::Value *>();
}

VariableDefExprAST *VariableDefExprAST::ParseVar(CompileUnit * unit,
                                                 CodeBlockAST *codeblock)
{
    TypeAST *typeAST = TypeAST::ParseType(unit);

    Token       nexToken = *(unit->icurTok);
    std::string idName   = nexToken.tokenValue;
    nexToken             = unit->next_tok();
    ExprAST *initValue   = nullptr;

    if (nexToken.type != tok_syntax || nexToken.tokenValue != ";") {
        if (nexToken.type == tok_syntax && nexToken.tokenValue == "=") {
            if (codeblock == nullptr) {
                CompileError e("全局变量初始化未实现");
                throw e;
            }
            unit->next_tok();
            initValue = ExprAST::ParseExpression(unit, codeblock, false);
        } else {
            CompileError e("Unknown token:" + nexToken.dump());
            throw e;
        }
    }

    std::cout << std::left << std::setw(35)
              << "Variable definition found:" << idName
              << " with type:" << typeAST->name << std::endl;
    return new VariableDefExprAST(unit, codeblock, idName, typeAST, initValue);
}
