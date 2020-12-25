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
#include "../CompileError.hpp"

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
//todo:调试用代码，请删除

	llvm::BasicBlock *entry = llvm::BasicBlock::Create(*unit->context, "entry",
			func);
	builder->SetInsertPoint(entry);
	if (proto->name == "testPuts") {
		llvm::Value *helloWorld = builder->CreateGlobalStringPtr(
				"just for debug!\n");
		std::vector<llvm::Type*> putsargs;
		putsargs.push_back(builder->getInt8Ty()->getPointerTo());
		llvm::ArrayRef<llvm::Type*> argsRef(putsargs);
		llvm::FunctionType *putsType = llvm::FunctionType::get(
				builder->getInt32Ty(), argsRef, false);
		//FunctionType *mainType = FunctionType::get(builder.getInt32Ty(), false);
		//3)创建“函数调用”，而不是创建函数
		//FunctionCallee mainFunc = mod->getOrInsertFunction("_alolang_4main",);
		llvm::FunctionCallee putsFunc = unit->module->getOrInsertFunction(
				"puts", putsType);

		//7、调用函数（<#理解：通过createXXX创建出来的所有指令都在SetInsertPoint后面#>）
		builder->CreateCall(putsFunc, helloWorld); //这是创建方法的指令

	}
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
	PrototypeAST *protoType = PrototypeAST::ParsePrototype(unit, true);
	std::cout << "Function definition found:" << protoType->name << std::endl;
	std::vector<ExprAST*> body;
	Token nexToken;
	while (true) {
		nexToken = unit->next_tok();
		if (nexToken.type == tok_eof) {
			//todo:错误处理
			CompileError e("Unexpexted EOF in function body");
			throw e;
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

