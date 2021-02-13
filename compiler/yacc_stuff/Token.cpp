/*
 * Token.cpp
 *
 *  Created on: Dec 16, 2020
 *      Author: zbc
 */

#include "Token.h"
#include <sstream>

Token::Token() {
	tokenValue = "";
}

Token::~Token() {
	// TODO Auto-generated destructor stub
}

std::string Token::dump() {
	//TODO 先这样写着吧，反正是调试用
	std::string typeStr;
	std::stringstream ss;
	switch (type) {
	case tok_err:
		typeStr = "tok_err";
		break;
	case tok_eof:
		typeStr = "tok_eof";
		break;
	case tok_fun:
		typeStr = "tok_fun";
		break;
	case tok_extern:
		typeStr = "tok_extern";
		break;
	case tok_identifier:
		typeStr = "tok_identifier";
		break;
	case tok_number:
		typeStr = "tok_number";
		break;
	case tok_type:
		typeStr = "tok_type";
		break;
	case tok_return:
		typeStr = "tok_return";
		break;
	case tok_return_type:
		typeStr = "tok_return_type";
		break;
	case tok_syntax:
		typeStr = "tok_syntax";
		break;
	default:
		typeStr = "未定义";
	}
	ss << "type:" << typeStr << ",data:" << tokenValue;
	return ss.str();
}
