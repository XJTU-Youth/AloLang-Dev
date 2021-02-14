#include "ExprAST.h"
#include "CallExprAST.h"
#include "IntExprAST.h"
#include "../CompileError.hpp"
#include <iostream>
#include "VariableExprAST.h"
#include "BinaryExprAST.h"

int GetTokPrecedence(Token tok) {
	if (tok.type != tok_syntax) {
		return -1;
	}
	std::map<char, int> BinopPrecedence;
	BinopPrecedence['+'] = 100;
	BinopPrecedence['-'] = 200;
	BinopPrecedence['*'] = 300;
	BinopPrecedence['/'] = 400;

	int TokPrec = BinopPrecedence[tok.tokenValue[0]];
	if (TokPrec <= 0) {
		return -1;
	}
	return TokPrec;

}

ExprAST::ExprAST(CompileUnit *unit) :
		BaseAST(unit) {
	// TODO Auto-generated constructor stub
}

ExprAST::~ExprAST() {
	// TODO Auto-generated destructor stub
}

ExprAST* ExprAST::ParsePrimary(CompileUnit *unit) {
	//todo:除了函数调用之外的语句解析
	Token token = unit->next_tok();
	switch (token.type) {
	case tok_number: {
		return new IntExprAST(unit, strtol(token.tokenValue.c_str(), NULL, 10));
	}
	case tok_identifier: {
		//函数调用或定义
		std::string idName = token.tokenValue;
		token = unit->next_tok();
		if (token.type == tok_identifier) {
			//定义
			std::string valName = token.tokenValue;
			return VariableExprAST::ParseVar(unit, valName, idName);
		} else if (token.tokenValue == "(") {
			std::vector<ExprAST*> args;
			while (true) {
				Token nextToken = *(unit->icurTok + 1);

				if (nextToken.type == tok_syntax && nextToken.tokenValue == ")") {
					break;
				}
				if (nextToken.type == tok_syntax && nextToken.tokenValue == ",") {
					continue;
				}

				ExprAST *arg = ExprAST::ParseExpression(unit, false);
				args.push_back(arg);
				//todo:异常处理
			}

			return new CallExprAST(unit, idName, args);
		} else {
			std::cerr << "err2:非函数调用或定义未实现" << std::endl;
		}
		break;
	}
	default: {
		CompileError e("不期待的token");
		throw e;
	}
	}
	return nullptr;
}

static ExprAST* ParseBinOpRHS(CompileUnit *unit, int ExprPrec, ExprAST *LHS) {
	while (1) {

		int TokPrec = GetTokPrecedence(*(unit->icurTok + 1));
		if (TokPrec < ExprPrec) {
			return LHS;
		}
		Token token = unit->next_tok();
		char BinOp = token.tokenValue[0];

		ExprAST *RHS = ExprAST::ParsePrimary(unit);
		if (!RHS)
			return nullptr;

		int NextPrec = GetTokPrecedence(*(unit->icurTok + 1));
		if (TokPrec < NextPrec) {
			token = unit->next_tok();
			RHS = ParseBinOpRHS(unit, TokPrec + 1, RHS);
			if (RHS == nullptr) {
				return nullptr;
			}
		}
		LHS = new BinaryExprAST(unit, BinOp, LHS, RHS);
	}
}

ExprAST* ExprAST::ParseExpression(CompileUnit *unit, bool root) {
	ExprAST *LHS = ParsePrimary(unit);
	if (LHS == nullptr) {
		return nullptr;
	}
	ExprAST *result = ParseBinOpRHS(unit, 0, LHS);
	if (root) {
		Token token = unit->next_tok();
		if (token.type != tok_syntax || token.tokenValue != ";") {
			CompileError e("丟失分号");
			throw e;
		}
	}
	return result;
}
