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
	tok_err = 0,
	tok_eof = -1,
	tok_fun = -2,
	tok_extern = -3,
	tok_identifier = -4,
	tok_number = -5,
	tok_type = -6,
	tok_return = -7,
	tok_return_type = -8,
	tok_syntax = -9
};

class Token {
public:
	Token();
	virtual ~Token();
	std::string dump();
	TokenType type;
	std::string tokenValue;
};

#endif /* COMPILER_TOKEN_H_ */
