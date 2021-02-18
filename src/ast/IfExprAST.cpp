/*
 * IfExprAST.cpp
 *
 *  Created on: Feb 17, 2021
 *      Author: zbc
 */

#include "IfExprAST.h"
#include "../CompileError.hpp"
#include "CodeBlockAST.h"

IfExprAST::IfExprAST(CompileUnit *unit, CodeBlockAST *parent,
                     ExprAST *condition, CodeBlockAST *thenBlock,
                     CodeBlockAST *elseBlock)
    : ExprAST(unit)
{
    this->parent    = parent;
    this->thenBlock = thenBlock;
    this->elseBlock = elseBlock;
    this->condition = condition;
}

IfExprAST::~IfExprAST()
{
    // TODO Auto-generated destructor stub
}

IfExprAST *IfExprAST::ParseIfExpr(CompileUnit *unit, CodeBlockAST *parent)
{
    ExprAST *condition = ExprAST::ParseExpression(unit, parent, false);
    unit->next_tok();
    CodeBlockAST *thenBlock = CodeBlockAST::ParseCodeBlock(unit, "", parent);
    CodeBlockAST *elseBlock = nullptr;

    if ((unit->icurTok + 1)->type == tok_key_else) {
        unit->next_tok();
        unit->next_tok();
        elseBlock = CodeBlockAST::ParseCodeBlock(unit, "", parent);
    }
    return new IfExprAST(unit, parent, condition, thenBlock, elseBlock);
}
llvm::Value *IfExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    llvm::Function *  function = builder->GetInsertBlock()->getParent();
    llvm::BasicBlock *thenBB   = thenBlock->Codegen(function);
    llvm::BasicBlock *elseBB   = elseBlock->Codegen(function);
    builder->CreateCondBr(condition->Codegen(builder), thenBB, elseBB);
    llvm::BasicBlock * MergeBB = llvm::BasicBlock::Create(*unit->context, "");
    llvm::IRBuilder<> *Builder = new llvm::IRBuilder<>(*unit->context);
    Builder->SetInsertPoint(thenBB);
    Builder->CreateBr(MergeBB);
    Builder->SetInsertPoint(elseBB);
    Builder->CreateBr(MergeBB);
    function->getBasicBlockList().push_back(MergeBB);

    builder->SetInsertPoint(MergeBB);
    return nullptr;
}
