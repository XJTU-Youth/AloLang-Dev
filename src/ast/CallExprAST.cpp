/*
 * CallExprAST.cpp
 *
 *  Created on: Dec 24, 2020
 *      Author: zbc
 */

#include "CallExprAST.h"
#include "../CompileError.hpp"
#include "ClassAST.h"
#include "ExternAST.h"
#include "FunctionAST.h"
#include "TypeAST.h"

#include <iostream>

#include "../utils.h"

CallExprAST::CallExprAST(CompileUnit *unit, FunctionAST *parentFunction,
                         const std::string &callee, ExprAST *args, ExprAST *LHS)
    : ExprAST(unit)
{
    this->callee         = callee;
    this->args           = args;
    this->LHS            = LHS;
    this->parentFunction = parentFunction;
    std::cout << std::left << std::setw(35)
              << "Function call found:" << this->callee << std::endl;
}

CallExprAST::~CallExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> CallExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    type.clear();
    std::vector<llvm::Value *> result;
    std::vector<TypeAST *>     argStr;
    std::vector<llvm::Value *> argsV = args->CodegenChain(builder);
    if (LHS != nullptr) {
        llvm::Value *thisV = nullptr;
        if (Lpointer) {
            thisV = LHS->Codegen(builder)[0];
        } else {
            thisV = LHS->getAlloca(builder);
        }
        if (thisV == nullptr) {
            CompileError e("No memory allocaed");
            throw e;
        }
        argsV.insert(argsV.begin(), thisV);
        if (LHS->type.size() != 1) {
            CompileError e("Multi/void value detected");
            throw e;
        }
        if (Lpointer) {
            if (parentFunction->parentClass == nullptr) {
                argStr.push_back(new TypeAST(unit, LHS->type[0]->pointee));
            } else {
                argStr.push_back(parentFunction->parentClass->getRealType(
                    new TypeAST(unit, LHS->type[0]->pointee)));
            }

        } else {
            if (parentFunction->parentClass == nullptr) {
                argStr.push_back(new TypeAST(unit, LHS->type[0]));
            } else {
                argStr.push_back(parentFunction->parentClass->getRealType(
                    new TypeAST(unit, LHS->type[0])));
            }
        }
    }
    for (TypeAST *ast : args->type) {
        if (parentFunction->parentClass == nullptr) {
            argStr.push_back(ast);
        } else {
            argStr.push_back(parentFunction->parentClass->getRealType(ast));
        }
    }
    std::string dname;
    if (LHS == nullptr) {
        dname = demangle(callee, argStr);
    } else {
        if (Lpointer) {
            ClassAST *baseClass =
                unit->classes[LHS->type[0]->pointee->baseClass];
            std::string typeMangledName =
                baseClass->getRealNameForMangle(LHS->type[0]->genericTypes);

            dname = demangle(callee, argStr, typeMangledName);

        } else {
            ClassAST *  baseClass = unit->classes[LHS->type[0]->baseClass];
            std::string typeMangledName =
                baseClass->getRealNameForMangle(LHS->type[0]->genericTypes);

            dname = demangle(callee, argStr, typeMangledName);
        }
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
    for (TypeAST *tAST : proto->returnTypes) {
        if (LHS == nullptr) {
            type.push_back(tAST);
        } else {
            ClassAST *baseClass;
            if (Lpointer) {
                baseClass = unit->classes[LHS->type[0]->pointee->baseClass];
            } else {
                baseClass = unit->classes[LHS->type[0]->baseClass];
            }
            type.push_back(baseClass->getRealType(tAST));
        }
    }

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
