/*
 * CompileUnit.h
 *
 *  Created on: Dec 16, 2020
 *      Author: zbc
 */

#ifndef COMPILER_COMPILEUNIT_H_
#define COMPILER_COMPILEUNIT_H_

#include <string>
#include <sstream>
#include "Token.h"

class CompileUnit {
public:
	CompileUnit(std::string source);
	virtual ~CompileUnit();
	void compile();
	Token next_tok();

	std::string source;
	std::istringstream sis;
	Token curTok;
};

#endif /* COMPILER_COMPILEUNIT_H_ */
