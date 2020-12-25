/*
 * utils.cpp
 *
 *  Created on: May 2, 2020
 *      Author: zbc
 */
#include <vector>
#include <string>
#include <sstream>
#include "CompileError.hpp"

char syntax[] = { '!', '%', '^', '&', '*', '(', ')', '+', '=', '{', '}', '|',
		'~', '[', ']', '\\', ';', '\'', ':', '"', ',', '<', '>', '?', '.', '/',
		'#', ' ' };

bool isSyntax(char c) {
	for (char tmp : syntax) {
		if (c == tmp) {
			return true;
		}
	}
	return false;
}

//从pos查找到下一个非空格字段
void skipSpace(const std::vector<std::string> &words, long unsigned int &i) {
	while (true) {
		i++;
		if (i >= words.size()) {
			//TODO:异常处理（未期待的结尾）
			CompileError e("Unexpected EOF");
			throw e;
		}
		if (words[i] != " ") {
			break;
		}
	}
}

void skipSpace(std::istream &in) {
	while (in.good() && isspace(in.peek())) {
		// Read and discard the space character
		in.ignore();
		//in.get();
	}
}
