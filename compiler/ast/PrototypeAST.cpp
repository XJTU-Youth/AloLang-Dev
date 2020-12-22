/*
 * PrototypeAST.cpp
 *
 *  Created on: Dec 21, 2020
 *      Author: zbc
 */

#include "PrototypeAST.h"
#include <iostream>

PrototypeAST::PrototypeAST(const std::string &name,
		const std::vector<std::string> &args) {
	std::cout << "Function definition found:" << name << std::endl;
}

PrototypeAST::~PrototypeAST() {
	// TODO Auto-generated destructor stub
}

llvm::Function* PrototypeAST::Codegen() {
	//todo:待实现
	return nullptr;
}
