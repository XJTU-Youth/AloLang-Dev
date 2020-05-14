#include "preprocessor.hpp"
#include "compileerror.hpp"
#include <vector>
#include "utils.h"
std::ifstream t_fin__;

std::map<std::string, std::string> variable;
int closeifstack = 0;
int currentifstack = 0;

std::string preProcess(std::string code, int cnt);


std::pair<std::string, std::string> genFactor(std::string line) {
	//std::pair<std::string,std::string> result;//分别为指令和参数
	int len = line.length();
	if (len < 2) {
		CompileError e("empty % indicator");
		throw e;
	}
	int i = 1;
	for (; i < len; i++) {
		if (line[i] == ' ') {
			break;
		}
	}
	if (i == len) {
		//预编译指令没有参数
		return std::pair<std::string, std::string>(line.substr(1, len - 1), "");
	} else {
		//预编译指令有参数
		return std::pair<std::string, std::string>(line.substr(1, i - 1),
				line.substr(i + 1, len - i - 1));
	}

}

std::string processPreInstruction(std::string line, int cnt) {
	std::pair<std::string, std::string> instruction = genFactor(line); //解析后的预编译指令
	if (instruction.first == "import") {
		t_fin__.open(instruction.second);
		if (!t_fin__.is_open()) {
			CompileError e("import file not found");
			throw e;
		}
		std::getline(t_fin__, line, char(EOF));
		t_fin__.close();
		return preProcess(line, cnt + 1);
	} else if (instruction.first == "def") {
		//解析宏定义
		std::string var, data;
		int len = instruction.second.length();
		if (len == 0) {
			CompileError e("no second instruction");
			throw e;
		}
		int i = 1;
		for (; i < len; i++) {
			if (instruction.second[i] == ' ') {
				break;
			}
		}
		if (i == len) {
			var = instruction.second.substr(0, len);
			data = "";
		} else {
			var = instruction.second.substr(0, i);
			data = instruction.second.substr(i + 1, len - i - 1);
		}
		variable[var] = data;
		return "";
	} else if (instruction.first == "rmdef") {
		if (instruction.second.length() == 0) {
			CompileError e("no second instruction");
			throw e;
		}
		if (!variable.erase(instruction.second)) {
			CompileError e("removing macro that doent exist");
			throw e;
			//找不到宏定义
		}
		return "";
	} else if (instruction.first == "ifdef") {
		if (instruction.second.length() == 0) {
			CompileError e("no second instruction");
			throw e;
		}
		if (closeifstack > 0) {
			closeifstack++;
		}
		if (variable.find(instruction.second) == variable.end()) {
			closeifstack++;
		}
		currentifstack++;
		return "";
	} else if (instruction.first == "ifndef") {
		if (instruction.second.length() == 0) {
			CompileError e("no second instruction");
			throw e;
		}
		if (closeifstack > 0) {
			closeifstack++;
		}
		if (variable.find(instruction.second) != variable.end()) {
			closeifstack++;
		}
		currentifstack++;
		return "";
	} else if (instruction.first == "endif") {
		if (currentifstack == 0) {
			CompileError e("no second instruction");
			throw e;
		}
		if (closeifstack > 0) {
			closeifstack--;
		}
		currentifstack--;
		return "";
	} else {
		CompileError e("Unrecognized preprocessor command");
		throw e;
	}
}

std::string findRealData(std::string key) {
	std::map<std::string, std::string>::iterator iter = variable.find(key);
	if (iter != variable.end()) {
		return findRealData(iter->second);
	} else {
		return key;
	}
}
//宏替换
std::string doReplace(std::string line) {
	std::vector<std::string> words;
	bool flag = false; //判断栈顶元素状态
	for (int i = 0; i < line.length(); i++) {
		if (isSyntax(line[i])) {
			words.push_back(std::string(1, line[i]));
			flag = false;
		} else {
			if (!flag) {
				words.push_back(std::string(1, line[i]));
				flag = true;
			} else {
				words[words.size() - 1] += std::string(1, line[i]);
			}
		}
	}
	std::stringstream ss;
	for (std::string tmp : words) {
		ss << findRealData(tmp);
	}
	return ss.str();
}

//递归预处理
std::string preProcess(std::string code, int cnt) {
	if (cnt == 128) {
		CompileError e("preprocessor recursion too deep");
		throw e;
	}
	std::istringstream buft_fin__(code);
	std::stringstream preprocessoroutput;
	std::string temp;
	bool isCommented = false;
	while (std::getline(buft_fin__, temp)) {
		if (closeifstack > 0 && temp.substr(0, 6) != "%endif"
				&& temp.substr(0, 7) != "%ifndef"
				&& temp.substr(0, 6) != "%ifdef") {
			continue;
		}
		if (temp[0] == '%') {
			std::string processedPreInstruction = processPreInstruction(temp,
					cnt);
			if (processedPreInstruction.size() > 0)
				preprocessoroutput << processedPreInstruction << std::endl;
		} else {
			std::string replaced = doReplace(temp);
			//处理块注释
			int position = replaced.find("*/");
			if (position != replaced.npos) {
				if (!isCommented) {
					//TODO:错误处理
				}
				replaced = replaced.substr(position + 2,
						replaced.length() - position - 2);
				isCommented = false;
			}
			if (isCommented) {
				replaced = "";
			}
			position = replaced.find("/*");
			if (position != replaced.npos) {
				replaced = replaced.substr(0, position);
				isCommented = true;
			}

			//处理行注释
			position = replaced.find("//");
			if (position != replaced.npos) {
				replaced = replaced.substr(0, position);
			}

			int plen = replaced.length();
			if (plen > 0) {
				preprocessoroutput << replaced << std::endl;
			}
		}
		temp.erase();
	}
	return preprocessoroutput.str();
}
