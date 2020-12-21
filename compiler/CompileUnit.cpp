/*
 * CompileUnit.cpp
 *
 *  Created on: Dec 16, 2020
 *      Author: zbc
 */

#include "CompileUnit.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <ast/ExprAST.h>
#include <ast/FunctionAST.h>
#include <utils.h>
#include <fstream>
#include <iostream>

void createIRWithIRBuilder();

CompileUnit::CompileUnit(std::string source) {
	this->source = source;
	this->sis = std::istringstream(source);
}

CompileUnit::~CompileUnit() {
}

//获取下一个Token
Token CompileUnit::next_tok() {
	Token token;
	skipSpace(sis);
	char lastChar = sis.get();
	std::string dataStr;
	if (std::isalpha(lastChar) || lastChar == '-' || lastChar == '>') { // 标志符: [a-zA-Z][a-zA-Z0-9]*
		dataStr = lastChar;
		while (std::isalnum((lastChar = sis.get())))
			dataStr += lastChar;
		if (dataStr == "fun") {
			token.type = tok_fun;
			return token;
		}
		if (dataStr == "extern") {
			token.type = tok_extern;
			return token;
		}
		if (dataStr == "return") {
			token.type = tok_return;
			return token;
		}
		if (dataStr == "->") {
			token.type = tok_return_type;
			return token;
		}
		token.tokenValue = dataStr;
		token.type = tok_identifier;
		return token;
	}
	int numTypeFlag = 10; //进制数
	int statusFlag = 0;//0未处理进制标识，1正在处理进制标识，2已处理进制标识
	//TODO 对浮点数的支持
	if (std::isdigit(lastChar) || lastChar == '.') {   // 数字: [0-9.]+
		do {
			if (statusFlag==1) {
				lastChar = sis.get();
				if (lastChar == 'b') {
					numTypeFlag = 2;
				} else if (lastChar == 'x') {
					numTypeFlag = 16;
				} else if (std::isdigit(lastChar)) {
					numTypeFlag = 8;
					dataStr += lastChar;
				} else {
					dataStr = "0";
				}
				statusFlag = 2;
				lastChar = sis.get();
				continue;
			}
			if (lastChar == '0' && statusFlag==0) {
				statusFlag = 1;
				continue;
			}
			dataStr += lastChar;
			lastChar = sis.get();
		} while (std::isdigit(lastChar) || lastChar == '.');
		token.type = tok_number;
		char tmp[256];
		sprintf(tmp, "%ld", strtol(dataStr.c_str(), NULL, numTypeFlag));
		token.tokenValue = tmp;
		return token;
	}
	if (lastChar == EOF) {
		token.type = tok_eof;
		return token;
	}
	token.type = tok_err;
	return token;   //todo:错误处理
}

void CompileUnit::compile() {
	do {
		curTok = next_tok();
		switch (curTok.type) {
		case tok_fun:
			FunctionAST::ParseDefinition(this);
			break;
		}
		std::cout << "Read token:" << curTok.dump() << std::endl;
	} while (curTok.type != tok_eof);
	createIRWithIRBuilder();
}
