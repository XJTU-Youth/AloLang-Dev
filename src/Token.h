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
    tok_key_fun,
    tok_key_op,
    tok_key_literal,
    tok_key_control,
    tok_key_switch
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
};

#endif /* COMPILER_TOKEN_H_ */
