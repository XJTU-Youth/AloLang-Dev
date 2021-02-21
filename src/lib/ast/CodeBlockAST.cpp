/*
 * CodeBlockAST.cpp
 *
 *  Created on: Dec 27, 2020
 *      Author: zbc
 */

#include "CodeBlockAST.h"
#include "../CompileError.hpp"
#include "VariableDefExprAST.h"
#include <iostream>

CodeBlockAST::CodeBlockAST(CompileUnit *unit, std::vector<ExprAST *> body,
                           std::string name, CodeBlockAST *parent)
    : BaseAST(unit)
{
    this->builder = new llvm::IRBuilder<>(*unit->context);
    this->body    = body;
    this->name    = name;
    this->parent  = parent;
    this->endBB   = nullptr;
}

CodeBlockAST::~CodeBlockAST()
{
    // TODO Auto-generated destructor stub
}

CodeBlockAST *
CodeBlockAST::ParseCodeBlock(CompileUnit *unit, std::string name,
                             CodeBlockAST *                          parent,
                             const std::vector<VariableDefExprAST *> args)
{
    Token token = *(unit->icurTok + 1);
    if (token.type == tok_syntax && token.tokenValue == "{") {
        unit->next_tok();
        CodeBlockAST *codeblock =
            new CodeBlockAST(unit, std::vector<ExprAST *>(), name, parent);
        std::vector<ExprAST *> &body = codeblock->body;
        for (VariableDefExprAST *argDef : args) {
            argDef->codeblock = codeblock;
            body.push_back(argDef);
        }
        while (true) {
            Token inBlockToken = *(unit->icurTok + 1);
            if (inBlockToken.type == tok_eof) {
                CompileError e("Unexpexted EOF in function body");
                throw e;
            }
            if (inBlockToken.type == tok_syntax &&
                inBlockToken.tokenValue == "}") {
                unit->next_tok();
                break;
            }
            body.push_back(ExprAST::ParseExpression(unit, codeblock, true));
        }
        return codeblock;
    } else {
        CompileError e("Expected codeblock");
        throw e;
    }
}

llvm::BasicBlock *CodeBlockAST::Codegen(llvm::Function *function)
{
    llvm::BasicBlock *bb =
        llvm::BasicBlock::Create(*unit->context, name, function);
    endBB = bb;
    builder->SetInsertPoint(bb);

    for (ExprAST *expr : body) {
        expr->Codegen(builder);
    }
    // builder->CreateRetVoid(); // todo:待处理
    if (parent == nullptr) {
        builder->CreateRetVoid();
    }

    return bb;
}
