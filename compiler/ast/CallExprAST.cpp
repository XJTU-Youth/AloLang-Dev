/*
 * CallExprAST.cpp
 *
 *  Created on: Dec 24, 2020
 *      Author: zbc
 */

#include "CallExprAST.h"
#include "../CompileError.hpp"

#include <iostream>

#include "../utils.h"

CallExprAST::CallExprAST(CompileUnit *unit, const std::string &callee,
		std::vector<ExprAST*> &args) :
		ExprAST(unit) {
	std::vector<std::string> argStr;
	for (ExprAST *ast : args) {
		argStr.push_back("int");
	}
	if (callee != "main" && callee != "testPuts") {
		this->callee = demangle(callee, argStr);
	}

	this->args = args;
	std::cout << "Function call found:" << this->callee << std::endl;

}

CallExprAST::~CallExprAST() {
	// TODO Auto-generated destructor stub
}

llvm::Value* CallExprAST::Codegen(llvm::IRBuilder<> *builder) {
	llvm::Function *CalleeF = unit->module->getFunction(callee);
	if (CalleeF == 0) {
		CompileError e("Function " + callee + " not found");
		throw e;
	}
	std::vector<llvm::Value*> argsV;

	// If argument mismatch error.
	if (CalleeF->arg_size() != args.size()) {
		CompileError e("Incorrect arguments passed");
		throw e;
	}

	for (unsigned i = 0, e = args.size(); i != e; ++i) {
		argsV.push_back(args[i]->Codegen(builder));
	}

	return builder->CreateCall(CalleeF,argsV);
}

