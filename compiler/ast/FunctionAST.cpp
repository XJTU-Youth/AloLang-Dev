/*
 * FunctionAST.cpp
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#include "FunctionAST.h"
#include <iostream>
#include <llvm/IR/IRBuilder.h>

FunctionAST::FunctionAST(CompileUnit* unit,PrototypeAST *proto, std::vector<ExprAST*>):BaseAST(unit) {
	this->proto = proto;
}

FunctionAST::~FunctionAST() {
	// TODO Auto-generated destructor stub
}

llvm::Function* FunctionAST::Codegen() {
	llvm::IRBuilder<> builder(*unit->context);
	llvm::Function *TheFunction = proto->Codegen();

	// Create a new basic block to start insertion into.
	//llvm::BasicBlock *BB = llvm::BasicBlock::Create(context, "entry",
			//TheFunction);
	//llvm::Builder.SetInsertPoint(BB);

	/*if (llvm::Value *RetVal = ->Codegen()) {
		// Finish off the function.
		llvm::Builder.CreateRet(RetVal);

		// Validate the generated code, checking for consistency.
		llvm::verifyFunction(*TheFunction);

		return TheFunction;
	}*/
	return TheFunction;

	//todo:异常处理
	return 0;
}

FunctionAST* FunctionAST::ParseFunction(CompileUnit *unit) {
	Token nexToken = unit->next_tok();  // identifier.
	if (nexToken.type != tok_identifier) {
		std::cout << "error1" << std::endl;
		//TODO:异常处理
	}
	std::string FnName = nexToken.tokenValue;
	nexToken = unit->next_tok();  // identifier.

	if (nexToken.type != tok_syntax || nexToken.tokenValue != "(") {
		std::cout << "error2" << std::endl;
		//TODO:异常处理
	}
	//TODO:实现参数解析,返回值解析,名称修饰
	nexToken = unit->next_tok();  // identifier.

	if (nexToken.type != tok_syntax || nexToken.tokenValue != ")") {
		std::cout << "error3" << std::endl;
		//TODO:异常处理
	}
	nexToken = unit->next_tok();
	if (nexToken.type != tok_syntax || nexToken.tokenValue != "{") {
		std::cout << "error4" << std::endl;
		//todo:错误处理
	}
	std::vector<ExprAST*> body;
	while (true) {
		nexToken = unit->next_tok();
		if (nexToken.type == tok_eof) {
			//todo:错误处理
		}
		if (nexToken.type == tok_syntax && nexToken.tokenValue == "}") {
			break;
		}
		body.push_back(ExprAST::ParseExpression(nexToken, unit));
		std::cout << "Read token in function:" << FnName << ",that is:"
				<< nexToken.dump() << std::endl;

	}

	return new FunctionAST(unit,new PrototypeAST(unit,FnName, std::vector<std::string>()),
			body);

}

