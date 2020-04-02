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

std::string input_file_name;
std::string buff;

int main(int argc, char* argv[])
{
	if (argc == 1){
		cerr << argv[0] << ": fatal error: no input files\ncompilation terminated\n";
		return 1;
	} else if (argc > 2){
		cerr << argv[0] << ": fatal error: too many arguments\ncompilation terminated\n";
	}else {
		std::string args[argc];
		for (char i = 1; i < argc; i++)
			args[i-1] = argv[i];
		if (args[0]=="--help"||args[0]=="-h"){
			cout << "Usage: " << argv[0] << " file_name\n";
			return 0;
		}else {
			input_file_name = args[1];
		}
		fin.open(input_file_name);
		std::getline (fin,buff,char(EOF));
		//todo: add compile codes here
	}
	return 0;
}