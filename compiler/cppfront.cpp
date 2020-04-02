// cppfront.cpp 第一版编译器使用的前端，将AloLang代码转换为C++代码
#include <iostream>
#include <sstream>
#include <fstream>

#include <regex>

std::ifstream fin;
std::ofstream fout;

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char* argv[])
{
	if (argc == 1){
		cerr << argv[0] << ": fatal error: " << "no input files\ncompilation terminated\n";
		return 1;
	} else {
		std::string args[argc];
		for (char i = 1; i < argc; i++)
			args[i-1] = argv[i];
	}

	//todo: put something here.
	return 0;
}