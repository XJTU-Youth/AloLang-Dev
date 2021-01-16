#include "ExprAST.h"
#include "CallExprAST.h"
#include "IntExprAST.h"
#include "../CompileError.hpp"
#include <iostream>

ExprAST::ExprAST(CompileUnit *unit) :
		BaseAST(unit) {
	// TODO Auto-generated constructor stub
}

ExprAST::~ExprAST() {
	// TODO Auto-generated destructor stub
}

ExprAST* ExprAST::ParseExpression(CompileUnit *unit) {
	//todo:除了函数调用之外的语句解析
	Token lastToken = unit->curTok;
	switch (lastToken.type) {
	case tok_number: {
		return new IntExprAST(unit,
				strtol(lastToken.tokenValue.c_str(), NULL, 10));
	}
	case tok_identifier: {
		std::string idName = lastToken.tokenValue;
		unit->curTok = unit->next_tok();
		if (unit->curTok.type != tok_syntax || unit->curTok.tokenValue != "(") {
			std::cerr << "err2:非函数调用未实现" << std::endl;
		}
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

		unit->curTok = unit->next_tok();
		if (unit->curTok.type != tok_syntax || unit->curTok.tokenValue != ";") {
			std::cerr << "结尾的分号丢失？" << std::endl;

		}
		return new CallExprAST(unit, idName, args);
	}
	default: {
		CompileError e("非函数调用未实现");
		throw e;
	}
	}
}
