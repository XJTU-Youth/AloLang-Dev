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

#include "ast/ClassAST.h"
#include "ast/ExprAST.h"
#include "ast/ExternAST.h"
#include "ast/FunctionAST.h"
#include "ast/TypeAST.h"
#include "ast/VariableDefExprAST.h"
#include "utils.h"
#include <fstream>
#include <iostream>

void initInnerType(CompileUnit *unit)
{
    unit->types.insert(std::pair<std::string, llvm::Type *>(
        "int", llvm::Type::getInt64Ty(*unit->context)));
    unit->types.insert(std::pair<std::string, llvm::Type *>(
        "double", llvm::Type::getDoubleTy(*unit->context)));
    unit->types.insert(std::pair<std::string, llvm::Type *>(
        "bool", llvm::Type::getInt1Ty(*unit->context)));
}

void scanToken(CompileUnit *unit)
{
    Token token;
    do {
        int tokenid      = unit->lexer->yylex();
        token.type       = TokenType(tokenid);
        token.lineno     = unit->lexer->lineno();
        token.tokenValue = unit->lexer->YYText();
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
        } else if (token.type == tok_str) {
            std::string str  = token.tokenValue;
            token.tokenValue = str.substr(1, str.length() - 2);
        }

        // Debug token dump
        // std::cout << token.dump() << std::endl;

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
    module       = new llvm::Module(name, *context);
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
    initInnerType(this);
    scanToken(this);
    while (icurTok->type != tok_eof) {
        switch (icurTok->type) {
        case tok_fun: {
            FunctionAST *func_ast = FunctionAST::ParseFunction(this);
            functions.insert(std::pair<std::string, FunctionAST *>(
                func_ast->getDemangledName(), func_ast));
            // llvm::Function *func = func_ast->Codegen();
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
            ExternAST *externast = ExternAST::ParseExtern(this);
            externs.insert(std::pair<std::string, ExternAST *>(
                externast->getDemangledName(), externast));
            break;
        }
        case tok_identifier: {
            //全局变量
            VariableDefExprAST *var =
                VariableDefExprAST::ParseVar(this, nullptr);
            Token token = next_tok();
            globalVariables.insert(
                std::pair<std::string, VariableDefExprAST *>(var->idName, var));
            break;
        }
        default:
            std::cerr << "unexpected token:" << icurTok->dump() << std::endl;
        }
    }
    std::cout << "Start codegen:" << name << std::endl;
    // todo:Class的Codegen
    std::map<std::string, VariableDefExprAST *>::iterator gVar_iter;
    for (gVar_iter = globalVariables.begin();
         gVar_iter != globalVariables.end(); gVar_iter++) {
        llvm::Value *gVarValue = gVar_iter->second->Codegen(nullptr);
        globalVariablesValue.insert(
            std::pair<std::string, std::pair<TypeAST *, llvm::Value *>>(
                gVar_iter->second->idName,
                std::pair<TypeAST *, llvm::Value *>(gVar_iter->second->type,
                                                    gVarValue)));
    }
    std::map<std::string, ExternAST *>::iterator extern_iter;
    for (extern_iter = externs.begin(); extern_iter != externs.end();
         extern_iter++) {
        extern_iter->second->Codegen();
    }
    std::map<std::string, FunctionAST *>::iterator function_iter;
    for (function_iter = functions.begin(); function_iter != functions.end();
         function_iter++) {
        function_iter->second->Codegen();
    }

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
