/*
 * FunctionAST.cpp
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#include "FunctionAST.h"
#include "PrototypeAST.h"
#include <iostream>
#include <llvm/IR/IRBuilder.h>

FunctionAST::FunctionAST(CompileUnit *unit, PrototypeAST *proto,
		std::vector<ExprAST*> body) :
		BaseAST(unit) {
	this->proto = proto;
	this->body = body;
	this->builder = new llvm::IRBuilder<>(*unit->context);

}

FunctionAST::~FunctionAST() {
	// TODO Auto-generated destructor stub
}

llvm::Function* FunctionAST::Codegen() {
	llvm::Function *func = proto->Codegen();
	llvm::BasicBlock *entry = llvm::BasicBlock::Create(*unit->context, "entry",
			func);
	builder->SetInsertPoint(entry);
	for (ExprAST *expr : body) {
		expr->Codegen(builder);
	}
	builder->CreateRetVoid();

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
	return func;
}

FunctionAST* FunctionAST::ParseFunction(CompileUnit *unit) {
	PrototypeAST *protoType = PrototypeAST::ParsePrototype(unit);
	std::cout << "Function definition found:" << protoType->name << std::endl;
	Token nexToken = unit->next_tok();
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
		std::cout << "Read token in function:" << protoType->name << ",that is:"
				<< nexToken.dump() << std::endl;

	}

	return new FunctionAST(unit, protoType, body);

}

