// cppfront.cpp 第一版编译器使用的前端，将AloLang代码转换为C++代码
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <regex>
#include <map>
#include "compileerror.hpp"
#include "preprocessor.h"
#include "utils.h"

std::ifstream fin;
std::ofstream fout;

using std::cout;
using std::cerr;
using std::endl;

std::string input_file_name;
std::string output_file_name;

// Start Compiler
// 替换字符串中所有给定序列

void compile(const std::string &source);

std::string& replace_all(std::string &str, const std::string &old_value,
		const std::string &new_value) {
	for (std::string::size_type pos(0); pos != std::string::npos; pos +=
			new_value.length()) {
		if ((pos = str.find(old_value, pos)) != std::string::npos)
			str.replace(pos, old_value.length(), new_value);
		else
			break;
	}
	return str;
}
/*
 * 修饰规则：
 * 加上_alolang_前缀
 * 每个段前面加上长度
 * 比如fun foobar(long a, int b)修饰为_alolang_6foobar4long3int
 */
std::string demangle(const std::string &line) {
	std::vector<std::string> words;
	bool flag = false; //判断栈顶元素状态，如果为false则代表栈顶元素为符号
	for (long unsigned int i = 0; i < line.length(); i++) {
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
	ss << "_alolang_";
	long unsigned int i = -1; //处理指针
	skipSpace(words, i);
	if (words[i] != "fun") {
		//TODO:异常处理
		CompileError s("demangle error 0x1");
		throw(s);
	}
	skipSpace(words, i);
	ss << words[i].length() << words[i];
	skipSpace(words, i);
	if (words[i] != "(") {
		//TODO:异常处理
		CompileError s("demangle error 0x2");
		throw(s);
	}
	while (true) {
		skipSpace(words, i);
		ss << words[i].length() << words[i]; //得到类型
		skipSpace(words, i); //得到变量名，但在这个阶段没用
		skipSpace(words, i);
		if (words[i] == ")") {
			break;
		}

		if (words[i] != ",") {
			//TODO:异常处理（逗号）
			CompileError s("demangle error 0x3");
			throw(s);
		}
	}
	return ss.str();
}

int main(int argc, char *argv[]) {
	if (argc == 1) { //检测参数不足并报错退出
		cerr << argv[0]
				<< ": fatal error: no input files\ncompilation terminated\n";
		return 1;
	} else if (argc > 2) { //监测参数过多并报错退出
		cerr << argv[0]
				<< ": fatal error: too many arguments\ncompilation terminated\n";
		return 1;
	} else {
		std::string args[argc];
		for (int i = 1; i < argc; i++)
			args[i - 1] = argv[i];
		if (args[0] == "--help" || args[0] == "-h") { //显示帮助信息
			cout << "Usage: " << argv[0] << " file_name\n";
			return 0;
		} else { //确定源文件名
			input_file_name = args[0];
			output_file_name = input_file_name + ".ac";
		}
		fin.open(input_file_name);
		if (!fin.is_open()) {
			cerr << argv[0]
					<< ": fatal error: file not found\ncompilation terminated\n";
			return 1;
		}
		std::string buff; //源码
		std::getline(fin, buff, char(EOF));
		std::string preProcessed;
		fin.close();
		//std::string header = "%import types\n";
		//buff = header + buff;
		try {
			preProcessed = preProcess(buff, 0);
			//cout << preProcessed;
			//todo:这行代码写的极不规范，尽快修改
			compile(preProcessed);
		} catch (const CompileError &e) {
			cerr << "Compile Error: " << e.what() << endl
					<< "Compilation Terminated\n";
			return 1;
		}
		//todo: 编译用代码放下面
		//std::string compiled = compile(preProcessed);
		//将编译结果输出到文件
		//fout.open(output_file_name);
		//fout << compiled;
	}
	return 0;
}
