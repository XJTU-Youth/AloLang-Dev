/*
 * Token.h
 *
 *  Created on: Dec 16, 2020
 *      Author: zbc
 */

#ifndef COMPILER_TOKEN_H_
#define COMPILER_TOKEN_H_

#include "TokenSource.h"
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
    tok_key_class,
    tok_key_sizeof,
    tok_kernel_comp,
    tok_kernel_call
};

class Token
{
  public:
    Token();
    virtual ~Token();
    std::string dump();
    TokenType   type;
    std::string tokenValue;
    TokenSource source;
};

#endif /* COMPILER_TOKEN_H_ */
