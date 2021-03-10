#ifndef _PREPROCESSOR_
#define _PREPROCESSOR_

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

typedef std::pair<std::pair<std::string, int>, std::string> Tline;

std::vector<Tline> preProcess(const std::string &code, int cnt, std::string FN);

#endif
