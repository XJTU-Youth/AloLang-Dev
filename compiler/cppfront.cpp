// cppfront.cpp 第一版编译器使用的前端，将AloLang代码转换为C++代码
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <regex>
#include <map>
#include "compileerror.hpp"
#include "preprocessor.hpp"

std::ifstream fin;
std::ofstream fout;

using std::cout;
using std::cerr;
using std::endl;

std::string input_file_name;
std::string output_file_name;

std::string compile(const std::string & source)
{
	std::istringstream sin(source);
	std::ostringstream sout;
	std::string output, buff;
	while(std::getline(sin, buff)){
		//process
		if (buff.empty())
			continue;
		buff.erase(0,buff.find_first_not_of(" "));
    		buff.erase(buff.find_last_not_of(" ") + 1);
		if (buff=="begin" || buff.substr(0,6)=="begin ")
			buff = "{";
		else if (buff=="end" || buff.substr(0,4)=="end ")
			buff = "}";
		// 继续加else if
		sout << buff << endl;
	}
	return sout.str();
}



int main(int argc, char *argv[]) 
{
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
		std::string preProcessed;
		fin.close();
		try {
			preProcessed = preProcess(buff, 0);
			//just for debug
			cout << preProcessed;
		} catch (CompileError e) {
			cerr << "Compile Error: " << e.what() << endl
					<< "Compilation Terminated\n";
			return 1;
		}
		//todo: 编译用代码放下面
		std::string compiled = compile(preProcessed);
		//将编译结果输出到文件
		fout.open(output_file_name);
		fout << compiled;
	}
	return 0;
}
