/*
 * CompileUnit.cpp
 *
 *  Created on: Dec 16, 2020
 *      Author: zbc
 */

#include "CompileUnit.h"
#include "CompileError.hpp"
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Verifier.h>

#include "ast/ExprAST.h"
#include "ast/ExternAST.h"
#include "ast/FunctionAST.h"
#include "utils.h"
#include <fstream>
#include <iostream>

void initInnerType(CompileUnit *unit)
{
    // int
    /*unit->types.insert(
        std::pair<std::string, TypeAST>("int", new TypeAST(unit, "int")));*/
}

void scanToken(CompileUnit *unit)
{
    Token token;
    do {
        int tokenid  = unit->lexer->yylex();
        token.type   = TokenType(tokenid);
        token.lineno = unit->lexer->lineno();
        switch (token.type) {
        tok_fun:
        tok_extern:
        tok_return:
        tok_return_type:
        tok_eof:
            break;
        default:
            token.tokenValue = unit->lexer->YYText();
        }
        // Deal with numbers
        if (token.type == tok_number) {
            int numTypeFlag = 10; //进制数
            if (token.tokenValue.substr(0, 2) == "0x" ||
                token.tokenValue.substr(0, 2) == "0X")
                numTypeFlag = 16;
            else if (token.tokenValue.substr(0, 2) == "0b" ||
                     token.tokenValue.substr(0, 2) == "0B")
                numTypeFlag = 2;
            else if (token.tokenValue.substr(0, 1) == "0")
                numTypeFlag = 8;
            char tmp[256];
            sprintf(tmp, "%ld",
                    strtol(token.tokenValue.c_str(), NULL, numTypeFlag));
            token.tokenValue = tmp;
        }

        // Debug token dump
        std::cout << token.dump() << std::endl;

        unit->tokenList.push_back(token);
    } while (token.type != tok_eof);

    unit->icurTok = unit->tokenList.begin();
}

CompileUnit::CompileUnit(std::string name, std::string source)
{
    this->name   = name;
    this->source = source;
    this->sis    = std::istringstream(source);
    this->lexer  = new yyFlexLexer(sis, std::cerr);
    context      = new llvm::LLVMContext();
    module       = new llvm::Module("test.ll", *context);
}

CompileUnit::~CompileUnit() {}

//获取下一个Token
Token CompileUnit::next_tok()
{
    icurTok++;
    Token token = *icurTok;
    return token;
}

void CompileUnit::compile()
{
    std::cout << "Start compiling:" << name << std::endl;
    scanToken(this);
    initInnerType(this);
    do {
        switch (icurTok->type) {
        case tok_fun: {
            FunctionAST *   func_ast = FunctionAST::ParseFunction(this);
            llvm::Function *func     = func_ast->Codegen();
            /*llvm::Type*
             type=llvm::FunctionType::get(llvm::Type::getVoidTy(*context),
             false);
             module->getOrInsertGlobal(func_ast->proto->name, func->getType());

             llvm::GlobalVariable
             *gVar=module->getNamedGlobal(func_ast->proto->name);
             gVar->setConstant(true);
             gVar->setInitializer(func);*/
            break;
        }
        case tok_extern: {
            Token token = next_tok();
            if (token.type == tok_eof) {
                CompileError e("Unexpected EOF in funtion body, line " +
                               std::to_string(token.lineno));
                throw e;
            }
            if (token.type == tok_fun) {
                ExternAST::ParseExtern(this)->Codegen();
            }
            // todo:对导出非函数符号的处理
            break;
        }
        default:

            std::cerr << "unexpected token:" << icurTok->dump() << std::endl;
        }
    } while (next_tok().type != tok_eof);
    build();
}

void CompileUnit::build()
{
    std::error_code EC;
    // TODO:OpenFlag对LLVM11兼容性的更改
    llvm::raw_fd_ostream OS(name + ".bc", EC);
    llvm::WriteBitcodeToFile(*module, OS);
    OS.flush();
}
