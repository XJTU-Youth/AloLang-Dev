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

std::vector<Tline> preProcess(const std::string &code, int cnt);


#endif
