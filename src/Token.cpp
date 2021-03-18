/*
 * Token.cpp
 *
 *  Created on: Dec 16, 2020
 *      Author: zbc
 */

#include "Token.h"
#include <iomanip>
#include <sstream>

Token::Token()
{
    tokenValue = "";
    type       = tok_err;
}

Token::~Token()
{
    // TODO Auto-generated destructor stub
}

std::string Token::dump()
{
    // TODO 先这样写着吧，反正是调试用
    std::string       typeStr;
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
    case tok_syntax:
        typeStr = "tok_syntax";
        break;
    case tok_str:
        typeStr = "tok_str";
        break;
    case tok_key_op:
        typeStr = "tok_key_op";
        break;
    case tok_key_literal:
        typeStr = "tok_key_literal";
        break;
    case tok_key_break:
        typeStr = "tok_key_break";
        break;
    case tok_key_continue:
        typeStr = "tok_key_continue";
        break;
    case tok_key_do:
        typeStr = "tok_key_do";
        break;
    case tok_key_else:
        typeStr = "tok_key_else";
        break;
    case tok_key_for:
        typeStr = "tok_key_for";
        break;
    case tok_key_foreach:
        typeStr = "tok_key_foreach";
        break;
    case tok_key_goto:
        typeStr = "tok_key_goto";
        break;
    case tok_key_if:
        typeStr = "tok_key_if";
        break;
    case tok_key_while:
        typeStr = "tok_key_while";
        break;
    case tok_key_switch:
        typeStr = "tok_key_switch";
        break;
    case tok_key_class:
        typeStr = "tok_key_class";
        break;
    default:
        typeStr = "not defined";
    }
    ss << std::right << std::setw(25) << source.file << ":" << std::left
       << std::setw(6) << source.lineno << " type:" << std::setw(16) << typeStr
       << " data:" << tokenValue;
    return ss.str();
}
