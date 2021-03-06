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
    unit->next_tok();
    ExprAST *     condition = ExprAST::ParseExpression(unit, parent, false);
    CodeBlockAST *thenBlock =
        CodeBlockAST::ParseCodeBlock(unit, "", parent->baseFunction, parent);
    CodeBlockAST *elseBlock = nullptr;

    if (unit->icurTok->type == tok_key_else) {
        unit->next_tok();
        elseBlock = CodeBlockAST::ParseCodeBlock(unit, "", parent->baseFunction,
                                                 parent);
    }
    return new IfExprAST(unit, parent, condition, thenBlock, elseBlock);
}
std::vector<llvm::Value *> IfExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    llvm::Function *function = builder->GetInsertBlock()->getParent();
    std::vector<llvm::Value *> conditionValues =
        condition->CodegenChain(builder);
    if (conditionValues.size() != 1) {
        CompileError e("Multi/Void type in condition found.");
        throw e;
    }
    llvm::Value *     conditionValue = conditionValues[0];
    llvm::BasicBlock *MergeBB =
        llvm::BasicBlock::Create(*unit->context, "", function);
    llvm::BasicBlock *thenBB = thenBlock->Codegen(function);
    if (elseBlock != nullptr) {
        llvm::BasicBlock *elseBB = elseBlock->Codegen(function);
        builder->CreateCondBr(conditionValue, thenBB, elseBB);
        if (!elseBlock->jumped) {
            builder->SetInsertPoint(elseBlock->endBB);
            builder->CreateBr(MergeBB);
        }
    } else {
        builder->CreateCondBr(conditionValue, thenBB, MergeBB);
    }
    if (!thenBlock->jumped) {
        builder->SetInsertPoint(thenBlock->endBB);
        builder->CreateBr(MergeBB);
    }
    builder->SetInsertPoint(MergeBB);
    parent->endBB = MergeBB;
    return std::vector<llvm::Value *>();
}
