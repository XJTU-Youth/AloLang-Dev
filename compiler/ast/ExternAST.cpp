/*
 * ExternAST.cpp
 *
 *  Created on: Dec 23, 2020
 *      Author: zbc
 */

#include "ExternAST.h"
#include <iostream>

ExternAST::ExternAST(CompileUnit *unit, PrototypeAST *proto) :
		BaseAST(unit) {
	this->proto=proto;
}

ExternAST::~ExternAST() {
	// TODO Auto-generated destructor stub
}

ExternAST* ExternAST::ParseExtern(CompileUnit *unit) {
	PrototypeAST* proto = PrototypeAST::ParsePrototype(unit);
	std::cout << "Function extern found:" << proto->name << std::endl;
	Token nexToken = unit->next_tok();
	if (nexToken.type != tok_syntax || nexToken.tokenValue != ";") {
		//todo:异常处理
	}
	return new ExternAST(unit, proto);
}

llvm::Function* ExternAST::Codegen() {
	proto->Codegen();
	//待实现
	return 0;
}
