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


std::string demangle(const std::string &fnName,
		const std::vector<std::string> &argTypes) {
	std::stringstream ss;
	ss << "_alolang_";
	ss << fnName.length() << fnName;
	for (std::string word : argTypes) {
		ss << word.length() << word; //得到类型
	}
	return ss.str();
}

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
