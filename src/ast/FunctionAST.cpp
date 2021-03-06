/*
 * FunctionAST.cpp
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#include "FunctionAST.h"
#include "../CompileError.hpp"
#include "ClassAST.h"
#include "CodeBlockAST.h"
#include "PrototypeAST.h"
#include "TypeAST.h"
#include "VariableDefExprAST.h"
#include "VariableExprAST.h"
#include <iomanip>
#include <iostream>
#include <llvm/IR/IRBuilder.h>

FunctionAST::FunctionAST(CompileUnit *unit, PrototypeAST *proto,
                         CodeBlockAST *body, ClassAST *parentClass)
    : BaseAST(unit)
{
    this->proto       = proto;
    this->body        = body;
    this->parentClass = parentClass;
}

FunctionAST::~FunctionAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Function *FunctionAST::Codegen(std::vector<TypeAST *> igenericTypes)
{
    llvm::Function *func = proto->Codegen(igenericTypes);
    unit->globalFunctions.insert(
        std::pair<std::string, std::pair<PrototypeAST *, llvm::Function *>>(
            func->getName(),
            std::pair<PrototypeAST *, llvm::Function *>(proto, func)));

    llvm::BasicBlock *bb = body->Codegen(func);
    // func->getBasicBlockList().push_back(bb);

    return func;
}

FunctionAST *FunctionAST::ParseFunction(CompileUnit *unit,
                                        ClassAST *   parentClass)
{
    PrototypeAST *protoType =
        PrototypeAST::ParsePrototype(unit, true, parentClass);
    if (parentClass != nullptr) {
        std::vector<TypeAST *> genericTypes;
        for (std::string gType : parentClass->genericTypes) {
            genericTypes.push_back(new TypeAST(unit, gType));
        }
        protoType->args.insert(
            protoType->args.begin(),
            std::pair<TypeAST *, std::string>(
                new TypeAST(unit, new TypeAST(unit, parentClass->className,
                                              genericTypes)),
                "this"));
    }
    std::cout << std::left << std::setw(35)
              << "Function definition found:" << protoType->name << std::endl;
    std::vector<VariableDefExprAST *> args;

    for (unsigned int i = 0; i < protoType->args.size(); i++) {
        std::pair<TypeAST *, std::string> arg = protoType->args[i];
        args.push_back(new VariableDefExprAST(unit, nullptr, arg.second,
                                              arg.first, nullptr, i));
    }
    FunctionAST *result =
        new FunctionAST(unit, protoType, nullptr, parentClass);

    CodeBlockAST *body =
        CodeBlockAST::ParseCodeBlock(unit, "entry", result, nullptr, args);
    result->body = body;

    return result;
}
