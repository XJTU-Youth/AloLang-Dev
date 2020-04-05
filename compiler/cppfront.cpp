// cppfront.cpp 第一版编译器使用的前端，将AloLang代码转换为C++代码
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <regex>
#include "compileerror.hpp"

std::ifstream fin;
std::ofstream fout;

using std::cout;
using std::cerr;
using std::endl;

std::string input_file_name;
std::string output_file_name;
std::string buff; //源码

std::pair<std::string, std::string> genFactor(std::string line) {
	//std::pair<std::string,std::string> result;//分别为指令和参数
	int len = line.length();
	if (len < 2) {
		//TODO:错误处理
	}
	int i = 1;
	for (int i = 1; i < line.length(); i++) {
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
				line.substr(i + 1, line.length() - i - 1));
	}

}

//预处理
void preProcess() {
	std::istringstream buffin(buff);
	std::stringstream preprocessoroutput;
	std::string temp;
	while (std::getline(buffin, temp)) {
		if (temp[0] == '%') {
			std::pair<std::string, std::string> instruction = genFactor(temp); //解析后的预编译指令
			//是预编译指令
			if(instruction.first=="import") {
				fin.open(instruction.second);
				std::getline(fin, temp, char(EOF));
				preprocessoroutput << temp << std::endl;
			}else{
				//TODO：错误处理
			}
		} else {
			preprocessoroutput << temp << std::endl;
		}
		temp.erase();
	}
	//just for debug
	cout<<preprocessoroutput.str();
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
		std::getline(fin, buff, char(EOF));
		fin.close();
		try{
			preProcess();
		}
		catch (CompileError e){
			cerr << "Compile Error: " << e.what() << endl <<"Compilation Terminated\n";
		}
		//todo: 编译用代码放下面

		//将编译结果输出到文件
	}
	return 0;
}
