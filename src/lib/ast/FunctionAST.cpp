/*
 * FunctionAST.cpp
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#include "FunctionAST.h"
#include "../CompileError.hpp"
#include "CodeBlockAST.h"
#include "PrototypeAST.h"
#include "VariableDefExprAST.h"
#include "VariableExprAST.h"
#include <iomanip>
#include <iostream>
#include <llvm/IR/IRBuilder.h>

FunctionAST::FunctionAST(CompileUnit *unit, PrototypeAST *proto,
                         CodeBlockAST *body)
    : BaseAST(unit)
{
    this->proto = proto;
    this->body  = body;
}

FunctionAST::~FunctionAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Function *FunctionAST::Codegen()
{
    llvm::Function *  func = proto->Codegen();
    llvm::BasicBlock *bb   = body->Codegen(func);
    // func->getBasicBlockList().push_back(bb);

    return func;
}

FunctionAST *FunctionAST::ParseFunction(CompileUnit *unit)
{
    PrototypeAST *protoType = PrototypeAST::ParsePrototype(unit, true);
    std::cout << std::left << std::setw(35)
              << "Function definition found:" << protoType->name << std::endl;
    std::vector<VariableDefExprAST *> args;
    for (unsigned int i = 0; i < protoType->args.size(); i++) {
        std::pair<TypeAST *, std::string> arg = protoType->args[i];
        args.push_back(new VariableDefExprAST(unit, nullptr, arg.second,
                                              arg.first, nullptr, i));
    }
    CodeBlockAST *body =
        CodeBlockAST::ParseCodeBlock(unit, "entry", nullptr, args);
    return new FunctionAST(unit, protoType, body);
}
std::string FunctionAST::getDemangledName() { return proto->demangledName; }
