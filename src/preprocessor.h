#ifndef _PREPROCESSOR_
#define _PREPROCESSOR_

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <sstream>
#include <string>

typedef std::pair<std::pair<std::string,int>,std::string> Tline;
//外层：first是行所在文件名和行号，second是行内容

std::vector<Tline> preProcess(const std::string &code, int cnt, std::string FN);


#endif
