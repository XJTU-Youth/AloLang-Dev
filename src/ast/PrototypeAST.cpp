/*
 * PrototypeAST.cpp
 *
 *  Created on: Dec 21, 2020
 *      Author: zbc
 */

#include "PrototypeAST.h"
#include "../CompileError.hpp"
#include "../utils.h"

#include <iostream>

PrototypeAST::PrototypeAST(CompileUnit *unit, const std::string &name,
		const std::vector<std::pair<std::string, std::string>> &args) :
		BaseAST(unit) {
	this->name = name;
	this->args = args;
}

PrototypeAST::~PrototypeAST() {
	// TODO Auto-generated destructor stub
}

PrototypeAST* PrototypeAST::ParsePrototype(CompileUnit *unit, bool hasBody) {
	std::vector<std::pair<std::string, std::string>> args;
	std::vector<std::string> argStr;
	Token token = unit->next_tok();  // identifier.
	if (token.type != tok_identifier) {
		std::cerr << "error1" << std::endl;
		//TODO:异常处理
	}

	std::string FnName = token.tokenValue;
	token = unit->next_tok();

	if (token.type != tok_syntax || token.tokenValue != "(") {
		std::cerr << "error2" << std::endl;
		//TODO:异常处理
	}

	while (true) {
		if (FnName == "main") {
			token = unit->next_tok();  // ).
			break;
		}
		token = unit->next_tok();
		if (token.type == tok_syntax && token.tokenValue == ",") {
			continue;
		}
		if (token.type == tok_syntax && token.tokenValue == ")") {
			break;
		}
		std::string type = token.tokenValue;
		//todo:错误处理
		token = unit->next_tok();
		std::string name = token.tokenValue;
		std::pair<std::string, std::string> pair;
		pair.first = type;
		pair.second = name;
		args.push_back(pair);
	}
	if (token.type != tok_syntax || token.tokenValue != ")") {
		std::cout << "error3" << std::endl;
		//TODO:异常处理
	}
	for (std::pair<std::string, std::string> pair : args) {
		argStr.push_back(pair.first);
	}
	if (FnName != "main") {
		FnName = demangle(FnName, argStr);
	}
	token = unit->next_tok();  // -> or ; or {

	if (token.type == tok_return_type) {
		while (true) {
			//todo:解析返回类型
			token = unit->next_tok();  // identifier.
			if (token.type == tok_syntax) {
				if (token.tokenValue == "{") {
					if (!hasBody) {
						CompileError e("Unexpected function body");
						throw e;
					}
					break;
				}
				if (token.tokenValue == ";") {
					if (hasBody) {
						CompileError e("Unexpected ;");
						throw e;
					}
					break;
				}
			}
		}
	} else {
		if (token.tokenValue == "{") {
			if (!hasBody) {
				CompileError e("Unexpected function body");
				throw e;
			}
		}
		if (token.tokenValue == ";") {
			if (hasBody) {
				CompileError e("Unexpected ;");
				throw e;
			}
		}
	}
	return new PrototypeAST(unit, FnName, args);
}

llvm::Function* PrototypeAST::Codegen() {
// Make the function type:  double(double,double) etc.
	/*
	 llvm::FunctionType *FT = llvm::FunctionType::get(Type::getDoubleTy(TheContext),llvm::Doubles, false);
	 */
	std::vector<llvm::Type*> llvmArgs;
	for (int i = 0; i < args.size(); i++) {
		llvmArgs.push_back(llvm::Type::getInt64Ty(*unit->context));
	}
	llvm::FunctionType *FT = llvm::FunctionType::get(
			llvm::Type::getVoidTy(*unit->context), llvmArgs, false);

	llvm::Function *F = llvm::Function::Create(FT,
			llvm::GlobalValue::ExternalLinkage, name, unit->module);

	// If F conflicted, there was already something named 'Name'.  If it has a
	// body, don't allow redefinition or reextern.
	//todo:重定义异常处理
	/*if (F->getName() != Name) {
	 // Delete the one we just made and get the existing one.
	 F->eraseFromParent();
	 F = TheModule->getFunction(Name);

	 // If F already has a body, reject this.
	 if (!F->empty()) {
	 ErrorF("redefinition of function");
	 return 0;
	 }

	 // If F took a different number of args, reject.
	 if (F->arg_size() != Args.size()) {
	 ErrorF("redefinition of function with different # args");
	 return 0;
	 }
	 }*/
//todo:参数处理
// Set names for all arguments.
	unsigned Idx = 0;
	for (llvm::Function::arg_iterator AI = F->arg_begin(); Idx != args.size();
			++AI, ++Idx) {
		AI->setName(args[Idx].second);

		// Add arguments to variable symbol table.
		//NamedValues[args[Idx]] = AI;
	}

	return F;
}
