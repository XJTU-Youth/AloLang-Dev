/*
 * CodeBlockAST.cpp
 *
 *  Created on: Dec 27, 2020
 *      Author: zbc
 */

#include "CodeBlockAST.h"
#include <iostream>
#include "../CompileError.hpp"

CodeBlockAST::CodeBlockAST(CompileUnit *unit, std::vector<ExprAST*> body,
		std::string name) :
		BaseAST(unit) {
	this->builder = new llvm::IRBuilder<>(*unit->context);
	this->body = body;
	this->name=name;
}

CodeBlockAST::~CodeBlockAST() {
	// TODO Auto-generated destructor stub
}

CodeBlockAST* CodeBlockAST::ParseCodeBlock(CompileUnit *unit,
		std::string name) {
	std::vector<ExprAST*> body;
	while (true) {
		unit->curTok = unit->next_tok();
		if (unit->curTok.type == tok_eof) {
			//todo:错误处理
			CompileError e("Unexpexted EOF in function body");
			throw e;
		}
		if (unit->curTok.type == tok_syntax && unit->curTok.tokenValue == "}") {
			break;
		}
		body.push_back(ExprAST::ParseExpression(unit->curTok, unit));
		std::cout << "Read token in block:" << unit->curTok.dump() << std::endl;
	}
	return new CodeBlockAST(unit, body, name);
}

llvm::BasicBlock* CodeBlockAST::Codegen() {
	llvm::BasicBlock *bb = llvm::BasicBlock::Create(*unit->context, name);
	builder->SetInsertPoint(bb);

	for (ExprAST *expr : body) {
		expr->Codegen(builder);
	}
	builder->CreateRetVoid();

	return bb;
}

