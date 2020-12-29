/*
 * FunctionAST.cpp
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#include "FunctionAST.h"
#include "PrototypeAST.h"
#include "CodeBlockAST.h"
#include <iostream>
#include <llvm/IR/IRBuilder.h>
#include "../CompileError.hpp"

FunctionAST::FunctionAST(CompileUnit *unit, PrototypeAST *proto,
		CodeBlockAST *body) :
		BaseAST(unit) {
	this->proto = proto;
	this->body = body;

}

FunctionAST::~FunctionAST() {
// TODO Auto-generated destructor stub
}

llvm::Function* FunctionAST::Codegen() {
	llvm::Function *func = proto->Codegen();
	llvm::BasicBlock *bb = body->Codegen();
	func->getBasicBlockList().push_back(bb);
	return func;
}

FunctionAST* FunctionAST::ParseFunction(CompileUnit *unit) {
	PrototypeAST *protoType = PrototypeAST::ParsePrototype(unit, true);
	std::cout << "Function definition found:" << protoType->name << std::endl;
	CodeBlockAST *body = CodeBlockAST::ParseCodeBlock(unit, "entry");
	return new FunctionAST(unit, protoType, body);

}

