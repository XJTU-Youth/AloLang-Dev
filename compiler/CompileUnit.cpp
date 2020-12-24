/*
 * CompileUnit.cpp
 *
 *  Created on: Dec 16, 2020
 *      Author: zbc
 */

#include "CompileUnit.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/Bitcode/BitcodeWriter.h>

#include "ast/ExprAST.h"
#include "ast/FunctionAST.h"
#include "ast/ExternAST.h"
#include "utils.h"
#include <fstream>
#include <iostream>

CompileUnit::CompileUnit(std::string source) {
	this->source = source;
	this->sis = std::istringstream(source);
	context = new llvm::LLVMContext();
	module = new llvm::Module("test.ll", *context);
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
		while (std::isalnum((lastChar = sis.peek()))) {
			lastChar = sis.get();
			dataStr += lastChar;
		}
		if (dataStr == "fun") {
			token.type = tok_fun;
			return token;
		}
		if (dataStr == "func") {
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
	int statusFlag = 0; //0未处理进制标识，1正在处理进制标识，2已处理进制标识
	//TODO 对浮点数的支持，对非long型数的支持
	bool firstRun = true;
	if (std::isdigit(lastChar) || lastChar == '.') {   // 数字: [0-9.]+
		do {
			if (!firstRun) {
				sis.get();
			} else {
				firstRun = false;
			}
			if (statusFlag == 1) {
				if (lastChar == 'b') {
					numTypeFlag = 2;
				} else if (lastChar == 'x' || lastChar == 'X') {
					numTypeFlag = 16;
				} else if (std::isdigit(lastChar)) {
					numTypeFlag = 8;
					dataStr += lastChar;
				} else {
					dataStr = "0";
				}
				statusFlag = 2;
				lastChar = sis.peek();
				continue;
			}
			if (lastChar == '0' && statusFlag == 0) {
				statusFlag = 1;
				lastChar = sis.peek();
				continue;
			}
			dataStr += lastChar;
			lastChar = sis.peek();
		} while (!isSyntax(lastChar));
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
	token.type = tok_syntax;
	token.tokenValue = lastChar;
	return token;   //todo:可能不严谨，仔细test
}

void CompileUnit::compile() {
	while ((curTok = next_tok()).type != tok_eof) {
		std::cout << "Read token:" << curTok.dump() << std::endl;

		switch (curTok.type) {
		case tok_fun: {
			FunctionAST *func_ast = FunctionAST::ParseFunction(this);
			llvm::Function *func = func_ast->Codegen();
			/*llvm::Type* type=llvm::FunctionType::get(llvm::Type::getVoidTy(*context),
					 false);
			module->getOrInsertGlobal(func_ast->proto->name, func->getType());

			llvm::GlobalVariable *gVar=module->getNamedGlobal(func_ast->proto->name);
			gVar->setConstant(true);
			gVar->setInitializer(func);*/
			break;
		}
		case tok_extern:
			curTok = next_tok();
			if (curTok.type == tok_eof) {
				//todo:异常处理
			}
			if (curTok.type == tok_fun) {
				ExternAST::ParseExtern(this);
			}
			//todo:对导出非函数符号的处理
			break;
		default:
			std::cerr << "unexpected token." << std::endl;
		}
	}
	build();
	//createIRWithIRBuilder();
}

void CompileUnit::build() {
	std::error_code EC;
	//TODO:OpenFlag对LLVM11兼容性的更改
	llvm::raw_fd_ostream OS("module", EC);
	llvm::WriteBitcodeToFile(*module, OS);
	OS.flush();
}
