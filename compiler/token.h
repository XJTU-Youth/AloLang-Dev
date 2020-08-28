/*
 * token.h
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#ifndef COMPILER_TOKEN_H_
#define COMPILER_TOKEN_H_

enum Token {
  tok_eof = -1,
  tok_fun = -2, tok_extern = -3,
  tok_identifier = -4, tok_number = -5, tok_type = -6,
  tok_return = -7,tok_return_type=-8
};


#endif /* COMPILER_TOKEN_H_ */
