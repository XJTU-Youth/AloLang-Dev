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
#include <iostream>
#include <iomanip>
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
    std::cout << std::left << std::setw(35) << "Function definition found:" << protoType->name << std::endl;
    CodeBlockAST *body = CodeBlockAST::ParseCodeBlock(unit, "entry");
    return new FunctionAST(unit, protoType, body);
}
