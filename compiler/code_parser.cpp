/*
 * code_parser.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: zbc
 */
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <ast/ExprAST.h>
#include <ast/FunctionAST.h>
#include <token.h>
#include <string>
#include <sstream>
#include <utils.h>
#include <fstream>
#include <iostream>

void createIRWithIRBuilder();

std::istringstream sis;

double numVal;
std::string identifierStr;
int curTok;

//获取下一个Token
int next_tok() {
	skipSpace(sis);
	char lastChar = sis.get();
	if (std::isalpha(lastChar) || lastChar == '-' || lastChar == '>') { // 标志符: [a-zA-Z][a-zA-Z0-9]*
		identifierStr = lastChar;
		while (std::isalnum((lastChar = sis.get())))
			identifierStr += lastChar;
		if (identifierStr == "fun")
			return tok_fun;
		if (identifierStr == "extern")
			return tok_extern;
		if (identifierStr == "return")
			return tok_return;
		if (identifierStr == "->")
			return tok_return_type;
		return tok_identifier;
	}
	if (std::isdigit(lastChar) || lastChar == '.') {   // 数字: [0-9.]+
		std::string NumStr;
		do {
			NumStr += lastChar;
			lastChar = sis.get();
		} while (std::isdigit(lastChar) || lastChar == '.');
		numVal = strtod(NumStr.c_str(), 0);
		return tok_number;
	}
	if (lastChar == EOF)
		return tok_eof;
	return 0;   //todo:错误处理
}

/*static ExprAST* ParseIdentifierExpr() {
 std::string IdName = identifierStr;

 next_tok();  // eat identifier.

 if (curTok != '(') // Simple variable ref.
 return new VariableExprAST(IdName);

 // Call.
 next_tok();  // eat (
 std::vector<ExprAST*> Args;
 if (CurTok != ')') {
 while (1) {
 ExprAST *Arg = ParseExpression();
 if (!Arg)
 return 0;
 Args.push_back(Arg);

 if (CurTok == ')')
 break;

 if (CurTok != ',')
 return Error("Expected ')' or ',' in argument list");
 getNextToken();
 }
 }
 }*/

void compile(const std::string &source) {
	sis = std::istringstream(source);
	do {
		curTok = next_tok();
		switch (curTok) {
		case tok_fun:
			FunctionAST::ParseDefinition();
			break;
		}
		std::cout << "Read token:" << curTok << std::endl;
	} while (curTok != tok_eof);
	createIRWithIRBuilder();
}
