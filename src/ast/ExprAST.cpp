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
	Token lastToken = unit->curTok;
	switch (lastToken.type) {
	case tok_number: {
		return new IntExprAST(unit,
				strtol(lastToken.tokenValue.c_str(), NULL, 10));
	}
	case tok_identifier: {
		//函数调用或定义
		std::string idName = lastToken.tokenValue;
		unit->curTok = unit->next_tok();
		if (unit->curTok.type == tok_identifier) {
			//定义
			std::string valName = unit->curTok.tokenValue;
			return VariableExprAST::ParseVar(unit, valName, idName);
		} else if (unit->curTok.tokenValue == "(") {
			std::vector<ExprAST*> args;
			while (true) {
				unit->curTok = unit->next_tok();

				if (unit->curTok.type == tok_syntax
						&& unit->curTok.tokenValue == ")") {
					break;
				}
				if (unit->curTok.type == tok_syntax
						&& unit->curTok.tokenValue == ",") {
					continue;
				}

				ExprAST *arg = ExprAST::ParseExpression(unit);
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
		CompileError e("非函数调用未实现");
		throw e;
	}
	}
	return nullptr;
}

static ExprAST* ParseBinOpRHS(CompileUnit *unit, int ExprPrec, ExprAST *LHS) {
	while (1) {
		unit->curTok = unit->next_tok();
		int TokPrec = GetTokPrecedence(unit->curTok);
		if (TokPrec < ExprPrec) {
			return LHS;
		}
		char BinOp = unit->curTok.tokenValue[0];
		unit->curTok = unit->next_tok();

		ExprAST *RHS = ExprAST::ParsePrimary(unit);
		if (!RHS)
			return nullptr;

		int NextPrec = GetTokPrecedence(unit->curTok);
		if (TokPrec < NextPrec) {
			RHS = ParseBinOpRHS(unit, TokPrec + 1, RHS);
			if (RHS == nullptr) {
				return nullptr;
			}
		}
		LHS = new BinaryExprAST(unit, BinOp, LHS, RHS);
	}
}

ExprAST* ExprAST::ParseExpression(CompileUnit *unit) {
	ExprAST *LHS = ParsePrimary(unit);
	if (LHS == nullptr) {
		return nullptr;
	}
	return ParseBinOpRHS(unit, 0, LHS);
}
