#include <CompileError.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <regex>
#include <map>
#include "preprocessor.h"
#include "utils.h"
#include "CompileUnit.h"

std::ifstream fin;
std::ofstream fout;

using std::cout;
using std::cerr;
using std::endl;

std::string input_file_name;
std::string output_file_name;

// 替换字符串中所有给定序列
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

int main(int argc, char *argv[]) {
	std::string args[argc];
	for (int i = 1; i < argc; i++)
		args[i - 1] = argv[i];
	 if (argc == 1) { //检测参数不足并报错退出
		cerr << argv[0]
				<< ": fatal error: no input files\ncompilation terminated\n";
		return 1;
	} else if (argc > 2) { //监测参数过多并报错退出
		cerr << argv[0]
				<< ": fatal error: too many arguments\ncompilation terminated\n";
		return 1;
	} else {
		if (args[0] == "--help" || args[0] == "-h") { //显示帮助信息
			cout << "Usage: " << argv[0] << " file_name\n";
			return 0;
		} else { //确定源文件名
			input_file_name = args[0];
			output_file_name = "alo.out";
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
			CompileUnit(preProcessed).compile();
			//下面代码仅用来方便调试
			system("llc ./module --relocation-model=pic");
			system("gcc ./module.s -fPIE -o alo.out");
		} catch (const CompileError &e) {
			cerr << "Compile Error: " << e.what() << endl
					<< "Compilation Terminated\n";
			return 1;
		}
	}
	return 0;
}
