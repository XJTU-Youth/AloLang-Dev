/*
 * ExternAST.cpp
 *
 *  Created on: Dec 23, 2020
 *      Author: zbc
 */

#include "ExternAST.h"
#include <iostream>

ExternAST::ExternAST(CompileUnit *unit, PrototypeAST *prototype) :
		BaseAST(unit) {
	// TODO Auto-generated constructor stub

}

ExternAST::~ExternAST() {
	// TODO Auto-generated destructor stub
}

ExternAST* ExternAST::ParseExtern(CompileUnit *unit) {
	PrototypeAST *protoType = PrototypeAST::ParsePrototype(unit);
	std::cout << "Function extern found:" << protoType->name << std::endl;
	Token nexToken = unit->next_tok();
	if (nexToken.type != tok_syntax || nexToken.tokenValue != ";") {
		//todo:异常处理
	}
	return new ExternAST(unit, protoType);
}

llvm::Function* ExternAST::Codegen() {
	//待实现
	return 0;
}
