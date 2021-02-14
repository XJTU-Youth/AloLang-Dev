/*
 * VariableExprAST.cpp
 *
 *  Created on: Jan 23, 2021
 *      Author: zbc
 */

#include "VariableExprAST.h"

#include "IntExprAST.h"
#include <iostream>

VariableExprAST::VariableExprAST(CompileUnit *unit, const std::string &idName,
		const std::string &type) :
		ExprAST(unit) {
	this->idName = idName;
	this->type = type;
}

VariableExprAST::~VariableExprAST() {
	// TODO Auto-generated destructor stub
}

static llvm::AllocaInst* CreateEntryBlockAlloca(CompileUnit *unit,
		llvm::Function *function, const std::string &VarName,
		const std::string &type) {
	llvm::IRBuilder<> builder(&function->getEntryBlock(),
			function->getEntryBlock().begin());
	return builder.CreateAlloca(llvm::Type::getInt64Ty(*unit->context), 0,
			VarName.c_str());
}

llvm::Value* VariableExprAST::Codegen(llvm::IRBuilder<> *builder) {
	//todo:待实现
	std::cout << "TODO:#2" << std::endl;
	llvm::BasicBlock *insertBlock = builder->GetInsertBlock();
	llvm::Function *function = insertBlock->getParent();
	llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(unit, function, idName,
			type);
	builder->CreateStore(IntExprAST(unit, 0).Codegen(builder), Alloca);

	return Alloca;
}

VariableExprAST* VariableExprAST::ParseVar(CompileUnit *unit, std::string idName,
		std::string type) {
	std::cout << "Variable definition found:" << idName << " with type:" << type
			<< std::endl;
	unit->curTok = unit->next_tok();
	if (unit->curTok.type != tok_syntax || unit->curTok.tokenValue != ";") {
		std::cerr << "TODO:#1" << std::endl;
	}
	return new VariableExprAST(unit, idName, type);
}

