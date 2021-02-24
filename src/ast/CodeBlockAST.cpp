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
    Token token = *unit->icurTok;
    if (token.type == tok_syntax && token.tokenValue == "{") {
        CodeBlockAST *codeblock =
            new CodeBlockAST(unit, std::vector<ExprAST *>(), name, parent);
        std::vector<ExprAST *> &body = codeblock->body;
        for (VariableDefExprAST *argDef : args) {
            argDef->codeblock = codeblock;
            body.push_back(argDef);
        }
        //解析块内语句
        Token inBlockToken = unit->next_tok();
        while (true) {
            inBlockToken = *(unit->icurTok);
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
    // builder->CreateRetVoid(); // todo:待处理,main特判
    // std::cout << name << std::string(function->getName()) << std::endl;
    if (parent == nullptr) {
        if (std::string(function->getName()) != "main") {
            builder->CreateRetVoid();
        } else {
            llvm::IntegerType *type =
                llvm::IntegerType::get(*unit->context, 32);
            llvm::ConstantInt *res = llvm::ConstantInt::get(type, 0, true);

            builder->CreateRet(res);
        }
    }

    return bb;
}
