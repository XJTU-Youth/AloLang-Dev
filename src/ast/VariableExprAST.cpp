/*
 * VariableExprAST.cpp
 *
 *  Created on: Jan 23, 2021
 *      Author: zbc
 */

#include "VariableExprAST.h"

#include "../CompileError.hpp"
#include "CodeBlockAST.h"
#include "IntExprAST.h"
#include "TypeAST.h"
#include <iostream>

VariableExprAST::VariableExprAST(CompileUnit *unit, CodeBlockAST *codeblock,
                                 const std::string &idName,
                                 const std::string &type)
    : ExprAST(unit)
{
    this->idName    = idName;
    this->type      = type;
    this->codeblock = codeblock;
    this->alloca    = nullptr;
    codeblock->namedValues.insert(
        std::pair<std::string, std::pair<std::string, VariableExprAST *>>(
            idName, std::pair<std::string, VariableExprAST *>(type, this)));
}

VariableExprAST::~VariableExprAST()
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

llvm::Value *VariableExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    // todo:待实现
    if (alloca == nullptr) {
        std::cout << "TODO:#2" << std::endl;
        llvm::BasicBlock *insertBlock = builder->GetInsertBlock();
        llvm::Function *  function    = insertBlock->getParent();
        alloca = CreateEntryBlockAlloca(unit, function, idName, type);
        builder->CreateStore(IntExprAST(unit, 4).Codegen(builder),
                             alloca); // todo:对类型的处理
    }
    return alloca;
}

VariableExprAST *VariableExprAST::ParseVar(CompileUnit * unit,
                                           CodeBlockAST *codeblock,
                                           std::string idName, std::string type)
{
    std::cout << std::left << std::setw(35)
              << "Variable definition found:" << idName << " with type:" << type
              << std::endl;
    Token nexToken = *(unit->icurTok + 1);
    if (nexToken.type != tok_syntax || nexToken.tokenValue != ";") {
        std::cerr << "TODO:变量初始化赋值" << std::endl;
    }
    return new VariableExprAST(unit, codeblock, idName, type);
}
