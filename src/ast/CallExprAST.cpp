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
#include "TypeAST.h"

#include <iostream>

#include "../utils.h"

CallExprAST::CallExprAST(CompileUnit *unit, const std::string &callee,
                         ExprAST *args, ExprAST *LHS)
    : ExprAST(unit)
{
    this->callee = callee;
    this->args   = args;
    this->LHS    = LHS;
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
    std::vector<TypeAST *>     argStr;
    std::vector<llvm::Value *> argsV = args->CodegenChain(builder);
    if (LHS != nullptr) {
        llvm::Value *thisV = LHS->getAlloca(builder);
        if (thisV == nullptr) {
            CompileError e("No memory allocaed");
            throw e;
        }
        argsV.insert(argsV.begin(), thisV);
        if (LHS->type.size() != 1) {
            CompileError e("Multi/void value detected");
            throw e;
        }
        argStr.push_back(new TypeAST(unit, LHS->type[0]));
    }
    for (TypeAST *ast : args->type) {
        argStr.push_back(ast);
    }
    std::string  dname;
    llvm::Value *LHSv; //新构造
    if (LHS == nullptr) {
        dname = demangle(callee, argStr);
    } else {
        LHSv  = LHS->Codegen(builder)[0];
        dname = demangle(callee, argStr, LHS->type[0]->getMangleName());
    }
    if (callee == "main") {
        dname = "main";
    }
    PrototypeAST *proto = nullptr;

    auto functionAST = unit->globalFunctions.find(dname);
    if (functionAST != unit->globalFunctions.end()) {
        proto = functionAST->second.first;
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
    } else {
        for (unsigned i = 0; i < type.size(); i++) {
            llvm::Value *member = builder->CreateExtractValue(retD, {i});
            result.push_back(member);
        }
    }
    return result;
}
