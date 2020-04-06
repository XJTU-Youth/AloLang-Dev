// cppfront.cpp 第一版编译器使用的前端，将AloLang代码转换为C++代码
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <regex>
#include <map>
#include "compileerror.hpp"

std::ifstream fin;
std::ofstream fout;

using std::cout;
using std::cerr;
using std::endl;

std::string input_file_name;
std::string output_file_name;

std::map<std::string, std::string> variable;
int closeifstack = 0;
int currentifstack = 0;

char syntax[] = { '!', '%', '^', '&', '*', '(', ')', '-', '+', '=', '{', '}',
		'|', '~', '[', ']', '\\', ';', '\'', ':', '"', ',', '<', '>', '?', '.',
		'/', '#' };

bool isSyntax(char c)
{
	for(char tmp:syntax)
	{
		if(c==tmp)
		{
			return true;
		}
	}
	return false;
}

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

//递归预处理
std::string preProcess(std::string code, int cnt) {
	if (cnt == 128) {
		CompileError e("preprocessor recursion too deep");
		throw e;
	}
	std::istringstream buffin(code);
	std::stringstream preprocessoroutput;
	std::string temp;
	while (std::getline(buffin, temp)) {
		if (closeifstack > 0 && temp.substr(0, 6) != "%endif"
				&& temp.substr(0, 7) != "%ifndef"
				&& temp.substr(0, 6) != "%ifdef") {
			continue;
		}
		if (temp[0] == '%') {
			std::pair<std::string, std::string> instruction = genFactor(temp); //解析后的预编译指令
			//是预编译指令
			if (instruction.first == "import") {
				fin.open(instruction.second);
				if (!fin.is_open()) {
					CompileError e("import file not found");
					throw e;
				}
				std::getline(fin, temp, char(EOF));
				fin.close();
				preprocessoroutput << preProcess(temp, cnt + 1) << std::endl;
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
			} else if (instruction.first == "endif") {
				if (currentifstack == 0) {
					CompileError e("no second instruction");
					throw e;
				}
				if (closeifstack > 0) {
					closeifstack--;
				}
				currentifstack--;
			} else {
				CompileError e("Unrecognized preprocessor command");
				throw e;
			}
		} else {
			preprocessoroutput << temp << std::endl;
		}
		temp.erase();
	}
	return preprocessoroutput.str();
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
		for (char i = 1; i < argc; i++)
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
		fin.close();
		try {
			std::string preProcessed = preProcess(buff, 0);
			//just for debug
			cout << preProcessed;
		} catch (CompileError e) {
			cerr << "Compile Error: " << e.what() << endl
					<< "Compilation Terminated\n";
			return 1;
		}
		//todo: 编译用代码放下面

		//将编译结果输出到文件
	}
	return 0;
}
