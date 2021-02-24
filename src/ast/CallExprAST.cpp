/*
 * CallExprAST.cpp
 *
 *  Created on: Dec 24, 2020
 *      Author: zbc
 */

#include "CallExprAST.h"
#include "../CompileError.hpp"
#include "ExternAST.h"
#include "FunctionAST.h"

#include <iostream>

#include "../utils.h"

CallExprAST::CallExprAST(CompileUnit *unit, const std::string &callee,
                         std::vector<ExprAST *> &args)
    : ExprAST(unit)
{
    this->callee = callee;
    this->args   = args;
    std::cout << std::left << std::setw(35)
              << "Function call found:" << this->callee << std::endl;
}

CallExprAST::~CallExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> CallExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> result;
    std::vector<llvm::Value *> argsV;

    for (unsigned i = 0, e = args.size(); i != e; ++i) {
        std::vector<llvm::Value *> r = args[i]->Codegen(builder);
        if (r.size() != 1) {
            CompileError e("Multi/Void type in args found.");
            throw e;
        }
        argsV.push_back(r[0]);
    }

    std::vector<TypeAST *> argStr;
    for (ExprAST *ast : args) {
        if (ast->type.size() != 1) {
            CompileError e("Multi/Void type found.");
            throw e;
        }
        argStr.push_back(ast->type[0]);
    }
    std::string dname = demangle(callee, argStr);
    if (callee == "main") {
        dname = "main";
    }
    PrototypeAST *proto = nullptr;

    auto externAST = unit->externs.find(dname);
    if (externAST != unit->externs.end()) {
        proto = externAST->second->proto;
    }

    auto functionAST = unit->functions.find(dname);
    if (functionAST != unit->functions.end()) {
        proto = functionAST->second->proto;
    }

    if (proto == nullptr) {
        CompileError e("Function " + dname + " not found.");
        throw e;
    }
    type = proto->returnTypes;

    llvm::Function *CalleeF = unit->module->getFunction(dname);
    if (CalleeF == 0) {
        CompileError e("Function " + dname + " not found in LLVM IR");
        throw e;
    }
    llvm::Value *retD = builder->CreateCall(CalleeF, argsV);
    if (proto->returnDirectly) {
        result.push_back(retD);
    }
    return result;
}
