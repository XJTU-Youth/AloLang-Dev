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

	Token nexToken = unit->next_tok();  // identifier.
	if (nexToken.type != tok_identifier) {
		std::cerr << "error1" << std::endl;
		//TODO:异常处理
	}
	std::string FnName = nexToken.tokenValue;
	nexToken = unit->next_tok();

	if (nexToken.type != tok_syntax || nexToken.tokenValue != "(") {
		std::cerr << "error2" << std::endl;
		//TODO:异常处理
	}

	while (true) {
		//todo：调试用代码，请删除
		if (FnName == "main" || FnName=="testPuts") {
			nexToken = unit->next_tok();  // ).
			break;
		}
		nexToken = unit->next_tok();
		if (nexToken.type == tok_syntax && nexToken.tokenValue == ",") {
			continue;
		}
		if (nexToken.type == tok_syntax && nexToken.tokenValue == ")") {
			break;
		}
		std::string type = nexToken.tokenValue;
		//todo:错误处理
		nexToken = unit->next_tok();
		std::string name = nexToken.tokenValue;
		std::pair<std::string, std::string> pair;
		pair.first = type;
		pair.second = name;
		args.push_back(pair);
	}
	if (nexToken.type != tok_syntax || nexToken.tokenValue != ")") {
		std::cout << "error3" << std::endl;
		//TODO:异常处理
	}
	for (std::pair<std::string, std::string> pair : args) {
		argStr.push_back(pair.first);
	}
	if (FnName != "main" && FnName != "testPuts") {
		FnName = demangle(FnName, argStr);
	}
	nexToken = unit->next_tok();  // -> or ; or {

	if (nexToken.type == tok_return_type) {
		while (true) {
			//todo:解析返回类型
			nexToken = unit->next_tok();  // identifier.
			if (nexToken.type == tok_syntax) {
				if (nexToken.tokenValue == "{") {
					if (!hasBody) {
						CompileError e("Unexpected function body");
						throw e;
					}
					break;
				}
				if (nexToken.tokenValue == ";") {
					if (hasBody) {
						CompileError e("Unexpected ;");
						throw e;
					}
					break;
				}
			}

		}
	} else {
		if (nexToken.tokenValue == "{") {
			if (!hasBody) {
				CompileError e("Unexpected function body");
				throw e;
			}
		}
		if (nexToken.tokenValue == ";") {
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
