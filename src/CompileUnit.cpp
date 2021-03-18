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
    unit->types.insert(std::pair<std::string, llvm::Type *>(
        "char", llvm::Type::getInt32Ty(*unit->context)));
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

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"int", "int", ">>"}, std::pair<llvm::Function *, TypeAST *>(
                                  nullptr, new TypeAST(unit, "int"))));

    unit->binOperators.insert(std::pair<std::array<std::string, 3>,
                                        std::pair<llvm::Function *, TypeAST *>>(
        {"int", "int", "<<"}, std::pair<llvm::Function *, TypeAST *>(
                                  nullptr, new TypeAST(unit, "int"))));

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
        {"double", "double", "%"}, std::pair<llvm::Function *, TypeAST *>(
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

void CompileUnit::ScanToken(std::vector<Tline> srclines)
{
    for (Tline line : srclines) {
        std::istringstream is(line.second);
        FlexLexer *        lexer = new yyFlexLexer(is, std::cerr);
        Token              token;

        while (1) {
            int tokenid      = lexer->yylex();
            token.type       = TokenType(tokenid);
            token.source     = line.first;
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
            // std::cout << token.dump() << std::endl;
            if (token.type == tok_eof)
                break;
            this->tokenList.push_back(token);
        }
    }
    Token TEOF;
    TEOF.type = tok_eof;
    this->tokenList.push_back(TEOF);
    this->icurTok = this->tokenList.begin();
}

CompileUnit::CompileUnit(std::string Iname)
{
    name         = Iname;
    context      = new llvm::LLVMContext();
    module       = new llvm::Module(name, *context);
    preprocessor = new Preprocessor(this);
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
    std::cout << "Start preproccessing and lexer:" << name << std::endl;
    std::vector<Tline> srclines = preprocessor->process();
    ScanToken(srclines);
    std::cout << "Start compiling:" << name << std::endl;

    initInnerType(this);
    initInnerOperations(this);
    while (icurTok->type != tok_eof) {
        switch (icurTok->type) {
        case tok_fun: {
            FunctionAST *func_ast = FunctionAST::ParseFunction(this);
            functions.push_back(func_ast);
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
            functions.push_back(externast);
            break;
        }
        case tok_identifier: {
            //全局变量
            VariableDefExprAST *var =
                VariableDefExprAST::ParseVar(this, nullptr);
            Token token = next_tok();
            globalVariables.push_back(var);
            break;
        }
        case tok_key_class: {
            ClassAST *classAST = ClassAST::ParseClass(this);
            classes.insert(std::pair<std::string, ClassAST *>(
                classAST->className, classAST));
            break;
        }
        default: {
            CompileError e("unexpected token:" + icurTok->dump(),
                           icurTok->source);
            throw e;
        }
        }
    }
    std::cout << "Start codegen:" << name << std::endl;
    /*for (ClassAST *classAST : classesO) {
        llvm::Type *classType = classAST->Codegen();
    }*/

    for (VariableDefExprAST *v : globalVariables) {
        v->Codegen(nullptr); //自动插入globalVariablesValue
    }
    std::map<std::string, ExternAST *>::iterator extern_iter;
    for (BaseAST *func : functions) {
        if (ExternAST *v = dynamic_cast<ExternAST *>(func)) {
            llvm::Function *f = v->Codegen();
            globalFunctions.insert(
                std::pair<std::string,
                          std::pair<PrototypeAST *, llvm::Function *>>(
                    f->getName(),
                    std::pair<PrototypeAST *, llvm::Function *>(v->proto, f)));

        } else if (FunctionAST *v = dynamic_cast<FunctionAST *>(func)) {
            llvm::Function *f = v->Codegen(); //自动插入globalFunctions

        } else {
            CompileError e("Unknown internal error.");
            throw e;
        }
    }

    build();
    std::cout << "Build finished." << std::endl;
}

void CompileUnit::build()
{
    std::error_code EC;
    // TODO:OpenFlag对LLVM11兼容性的更改
    llvm::raw_fd_ostream OS(name + ".bc", EC);
    llvm::WriteBitcodeToFile(*module, OS);
    OS.flush();
}
