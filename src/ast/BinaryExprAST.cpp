/*
 * BinaryExprAST.cpp
 *
 *  Created on: Feb 12, 2021
 *      Author: zbc
 */

#include "BinaryExprAST.h"

BinaryExprAST::BinaryExprAST(CompileUnit *unit, char binOP, ExprAST *LHS,
		ExprAST *RHS) :
		ExprAST(unit) {
	this->binOP = binOP;
	this->LHS = LHS;
	this->RHS = RHS;
}

BinaryExprAST::~BinaryExprAST() {
// TODO Auto-generated destructor stub
}

llvm::Value* BinaryExprAST::Codegen(llvm::IRBuilder<> *builder) {
	llvm::Value *L = LHS->Codegen(builder);
	llvm::Value *R = RHS->Codegen(builder);
	if (L == nullptr || R == 0)
		return 0;

	switch (binOP) {
	case '+':
		return builder->CreateAdd(L, R);
	case '-':
		return builder->CreateSub(L, R);
	case '*':
		return builder->CreateMul(L, R);
	case '/':
		return builder->CreateFDiv(L, R);
	default:
		return nullptr;
		//todo:异常处理
	}
}
