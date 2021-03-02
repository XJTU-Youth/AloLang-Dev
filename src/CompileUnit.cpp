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
#include <array>
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

void initInnerOperations(CompileUnit *unit)
{
    // binOP
    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"int", "int", "+"}, std::pair<llvm::Function *, TypeAST *>(
                                 nullptr, new TypeAST(unit, "int"))));
    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"int", "int", "-"}, std::pair<llvm::Function *, TypeAST *>(
                                 nullptr, new TypeAST(unit, "int"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"int", "int", "*"}, std::pair<llvm::Function *, TypeAST *>(
                                 nullptr, new TypeAST(unit, "int"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"int", "int", "/"}, std::pair<llvm::Function *, TypeAST *>(
                                 nullptr, new TypeAST(unit, "double"))));
    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"int", "int", "%"}, std::pair<llvm::Function *, TypeAST *>(
                                 nullptr, new TypeAST(unit, "int"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"int", "int", ">"}, std::pair<llvm::Function *, TypeAST *>(
                                 nullptr, new TypeAST(unit, "bool"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"int", "int", "<"}, std::pair<llvm::Function *, TypeAST *>(
                                 nullptr, new TypeAST(unit, "bool"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"int", "int", ">="}, std::pair<llvm::Function *, TypeAST *>(
                                  nullptr, new TypeAST(unit, "bool"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"int", "int", "<="}, std::pair<llvm::Function *, TypeAST *>(
                                  nullptr, new TypeAST(unit, "bool"))));
    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"int", "int", "!="}, std::pair<llvm::Function *, TypeAST *>(
                                  nullptr, new TypeAST(unit, "bool"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"int", "int", "=="}, std::pair<llvm::Function *, TypeAST *>(
                                  nullptr, new TypeAST(unit, "bool"))));
    // double
    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"double", "double", "+"}, std::pair<llvm::Function *, TypeAST *>(
                                       nullptr, new TypeAST(unit, "double"))));
    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"double", "double", "-"}, std::pair<llvm::Function *, TypeAST *>(
                                       nullptr, new TypeAST(unit, "double"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"double", "double", "*"}, std::pair<llvm::Function *, TypeAST *>(
                                       nullptr, new TypeAST(unit, "double"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"double", "double", "/"}, std::pair<llvm::Function *, TypeAST *>(
                                       nullptr, new TypeAST(unit, "double"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"double", "double", ">"}, std::pair<llvm::Function *, TypeAST *>(
                                       nullptr, new TypeAST(unit, "bool"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"double", "double", "<"}, std::pair<llvm::Function *, TypeAST *>(
                                       nullptr, new TypeAST(unit, "bool"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"double", "double", ">="}, std::pair<llvm::Function *, TypeAST *>(
                                        nullptr, new TypeAST(unit, "bool"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"double", "double", "<="}, std::pair<llvm::Function *, TypeAST *>(
                                        nullptr, new TypeAST(unit, "bool"))));
    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"double", "double", "!="}, std::pair<llvm::Function *, TypeAST *>(
                                        nullptr, new TypeAST(unit, "bool"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"double", "double", "=="}, std::pair<llvm::Function *, TypeAST *>(
                                        nullptr, new TypeAST(unit, "bool"))));
}

void scanToken(CompileUnit *unit)
{
    for (Tline line : unit->srclines) {
        std::istringstream is(line.second);
        FlexLexer *        lexer = new yyFlexLexer(is, std::cerr);
        Token              token;

        while (1) {
            int tokenid      = lexer->yylex();
            token.type       = TokenType(tokenid);
            token.file       = line.first.first;
            token.lineno     = line.first.second;
            token.tokenValue = lexer->YYText();
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
                if (token.tokenValue.find(".") != std::string::npos)
                    sprintf(tmp, "%f", strtod(token.tokenValue.c_str(), NULL));
                else
                    sprintf(
                        tmp, "%ld",
                        strtol(token.tokenValue.c_str(), NULL, numTypeFlag));
                token.tokenValue = tmp;
            } else if (token.type == tok_str) {
                std::string str  = token.tokenValue;
                token.tokenValue = str.substr(1, str.length() - 2);
            }

            // Debug token dump
            std::cout << token.dump() << std::endl;
            if (token.type == tok_eof)
                break;
            unit->tokenList.push_back(token);
        }
    }
    Token TEOF;
    TEOF.type = tok_eof;
    unit->tokenList.push_back(TEOF);
    unit->icurTok = unit->tokenList.begin();
}

CompileUnit::CompileUnit(std::string Iname, std::vector<Tline> lines)
{
    name     = Iname;
    srclines = lines;
    context  = new llvm::LLVMContext();
    module   = new llvm::Module(name, *context);
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
    initInnerOperations(this);
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
             module->getOrInsertGlobal(func_ast->proto->name,
             func->getType());

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
        case tok_key_class: {
            ClassAST *classAST = ClassAST::ParseClass(this);
            classes.insert(std::pair<std::string, ClassAST *>(
                classAST->className, classAST));
            classesO.push_back(classAST);
            break;
        }
        default: {
            CompileError e("unexpected token:" + icurTok->dump());
            throw e;
        }
        }
    }
    std::cout << "Start codegen:" << name << std::endl;
    /*for (ClassAST *classAST : classesO) {
        llvm::Type *classType = classAST->Codegen();
    }*/

    std::map<std::string, VariableDefExprAST *>::iterator gVar_iter;
    for (gVar_iter = globalVariables.begin();
         gVar_iter != globalVariables.end(); gVar_iter++) {
        gVar_iter->second->Codegen(nullptr);
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
