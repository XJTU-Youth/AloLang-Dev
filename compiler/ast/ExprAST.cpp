#include "ExprAST.h"
#include "CallExprAST.h"
#include <iostream>

ExprAST::ExprAST(CompileUnit *unit) :
		BaseAST(unit) {
	// TODO Auto-generated constructor stub

}

ExprAST::~ExprAST() {
	// TODO Auto-generated destructor stub
}

ExprAST* ExprAST::ParseExpression(Token lastToken,CompileUnit *unit) {
	//todo:除了函数调用之外的语句解析
	if (lastToken.type != tok_identifier) {
		std::cerr << "err1:非函数调用未实现" << std::endl;
	}
	std::string idName = lastToken.tokenValue;
	Token nexToken = unit->next_tok();
	if (nexToken.type != tok_syntax || nexToken.tokenValue != "(") {
		std::cerr << "err2:非函数调用未实现" << std::endl;

	}
	nexToken = unit->next_tok();
	if (nexToken.type != tok_syntax || nexToken.tokenValue != ")") {
		std::cerr << "err3:带参数调用未实现" << std::endl;

	}
	std::vector<ExprAST*> args;
	std::cout << "Call definition found:" << idName << std::endl;
	nexToken = unit->next_tok();
	if (nexToken.type != tok_syntax || nexToken.tokenValue != ";") {
		std::cerr << "结尾的分号丢失？" << std::endl;

	}
	return new CallExprAST(unit, idName, args);
}
