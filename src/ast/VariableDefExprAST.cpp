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

VariableDefExprAST::VariableDefExprAST(CompileUnit *      unit,
                                       const std::string &idName,
                                       const std::string &type,
                                       ExprAST *initValue, int argID)
    : ExprAST(unit)
{
    this->idName    = idName;
    this->type      = type;
    this->alloca    = nullptr;
    this->initValue = initValue;
    this->argID     = argID;
}

VariableDefExprAST::~VariableDefExprAST()
{
    // TODO Auto-generated destructor stub
}

static llvm::AllocaInst *CreateEntryBlockAlloca(CompileUnit *      unit,
                                                llvm::Function *   function,
                                                const std::string &VarName,
                                                const std::string &type)
{
    llvm::IRBuilder<> builder(&function->getEntryBlock(),
                              function->getEntryBlock().begin());
    auto              typeAST = unit->types.find(type);
    if (typeAST == unit->types.end()) {
        CompileError e("can't find type:" + type);
        throw e;
    }

    return builder.CreateAlloca(typeAST->second->Codegen(), 0, VarName.c_str());
}

llvm::Value *VariableDefExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    if (alloca == nullptr) {
        llvm::BasicBlock *insertBlock = builder->GetInsertBlock();
        llvm::Function *  function    = insertBlock->getParent();
        alloca = CreateEntryBlockAlloca(unit, function, idName, type);
        if (argID != -1) {
            builder->CreateStore(function->getArg(argID), alloca);
        }
        if (initValue != nullptr) {
            builder->CreateStore(initValue->Codegen(builder), alloca);
        }
    }
    return builder->CreateLoad(alloca);
}

VariableDefExprAST *VariableDefExprAST::ParseVar(CompileUnit * unit,
                                                 CodeBlockAST *codeblock,
                                                 std::string   idName,
                                                 std::string   type)
{
    std::cout << std::left << std::setw(35)
              << "Variable definition found:" << idName << " with type:" << type
              << std::endl;
    Token    nexToken  = *(unit->icurTok + 1);
    ExprAST *initValue = nullptr;

    if (nexToken.type != tok_syntax || nexToken.tokenValue != ";") {
        if (nexToken.type == tok_syntax && nexToken.tokenValue == "=") {
            unit->next_tok();
            initValue = ExprAST::ParseExpression(unit, codeblock, false);
        } else {
            CompileError e("Unknown token:" + nexToken.dump());
            throw e;
        }
    }
    return new VariableDefExprAST(unit, idName, type, initValue);
}
