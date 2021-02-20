/*
 * WhileExprAST.cpp
 *
 *  Created on: Feb 20, 2021
 *      Author: zbc
 */

#include "WhileExprAST.h"
#include "CodeBlockAST.h"

WhileExprAST::WhileExprAST(CompileUnit *unit, CodeBlockAST *codeblock,
                           ExprAST *condition, CodeBlockAST *body)
    : ExprAST(unit)
{
    this->condition = condition;
    this->body      = body;
    this->parent    = codeblock;
}

WhileExprAST::~WhileExprAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Value *WhileExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    llvm::Function *function = builder->GetInsertBlock()->getParent();

    llvm::BasicBlock *MergeBB =
        llvm::BasicBlock::Create(*unit->context, "", function);
    llvm::BasicBlock *bodyBB = body->Codegen(function);
    builder->CreateBr(bodyBB);
    builder->SetInsertPoint(body->endBB);
    llvm::Value *conditionValue = condition->Codegen(builder);
    builder->CreateCondBr(conditionValue, bodyBB, MergeBB);
    builder->SetInsertPoint(MergeBB);
    parent->endBB = MergeBB;
    return nullptr;
}

WhileExprAST *WhileExprAST::ParseWhileExpr(CompileUnit * unit,
                                           CodeBlockAST *parent)
{
    ExprAST *condition = ExprAST::ParseExpression(unit, parent, false);
    unit->next_tok();
    CodeBlockAST *body = CodeBlockAST::ParseCodeBlock(unit, "", parent);
    return new WhileExprAST(unit, parent, condition, body);
}
