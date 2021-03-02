/*
 * Token.h
 *
 *  Created on: Dec 16, 2020
 *      Author: zbc
 */

#ifndef COMPILER_TOKEN_H_
#define COMPILER_TOKEN_H_

#include <string>

enum TokenType {
    tok_err,
    tok_eof,
    tok_fun,
    tok_extern,
    tok_identifier,
    tok_number,
    tok_type,
    tok_return,
    tok_return_type,
    tok_syntax,
    tok_str,
    tok_key_op,
    tok_key_literal,
    tok_key_break,
    tok_key_continue,
    tok_key_do,
    tok_key_else,
    tok_key_for,
    tok_key_foreach,
    tok_key_goto,
    tok_key_if,
    tok_key_while,
    tok_key_switch,
    tok_key_class
};

class Token
{
  public:
    Token();
    virtual ~Token();
    std::string dump();
    TokenType   type;
    std::string tokenValue;
    uint64_t    lineno;
    std::string file;
};

#endif /* COMPILER_TOKEN_H_ */
