/*
 * FunctionAST.cpp
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#include "FunctionAST.h"

FunctionAST::FunctionAST() {
	// TODO Auto-generated constructor stub

}

FunctionAST::~FunctionAST() {
	// TODO Auto-generated destructor stub
}

llvm::Function* FunctionAST::Codegen() {
	//todo:待实现
	return nullptr;
}

PrototypeAST* FunctionAST::ParseDefinition(CompileUnit *unit) {
	Token nexToken = unit->next_tok();  // identifier.
	if (nexToken.type != tok_identifier) {
		//TODO:异常处理
	}
	std::string FnName = nexToken.tokenValue;
	nexToken = unit->next_tok();  // identifier.

	if (nexToken.type != tok_syntax || nexToken.tokenValue != "(") {
		//TODO:异常处理
		//return ErrorP("Expected '(' in prototype");
	}
	//TODO:实现参数解析,名称修饰
	nexToken = unit->next_tok();  // identifier.

	if (nexToken.type != tok_syntax || nexToken.tokenValue != ")") {
		//TODO:异常处理
		//return ErrorP("Expected '(' in prototype");
	}

	return new PrototypeAST(FnName, std::vector<std::string>());

}

