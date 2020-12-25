/*
 * CallExprAST.cpp
 *
 *  Created on: Dec 24, 2020
 *      Author: zbc
 */

#include "CallExprAST.h"
#include "../CompileError.hpp"

#include <iostream>

CallExprAST::CallExprAST(CompileUnit *unit, const std::string &callee,
		std::vector<ExprAST*> &args) :
		ExprAST(unit) {
	this->callee = callee;
	this->args = args;
}

CallExprAST::~CallExprAST() {
	// TODO Auto-generated destructor stub
}

llvm::Value* CallExprAST::Codegen(llvm::IRBuilder<> *builder) {
	llvm::Function *CalleeF = unit->module->getFunction(callee);
	if (CalleeF == 0) {
		CompileError e("Unknown function referenced");
		throw e;

	}
	std::vector<llvm::Value*> argsV;

	// If argument mismatch error.
	/*if (CalleeF->arg_size() != args.size())
	 return ErrorV("Incorrect # arguments passed");

	 for (unsigned i = 0, e = Args.size(); i != e; ++i) {
	 ArgsV.push_back(Args[i]->Codegen());
	 if (ArgsV.back() == 0)
	 return 0;
	 }*/

	return builder->CreateCall(CalleeF);
}

