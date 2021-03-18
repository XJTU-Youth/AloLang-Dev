#ifndef _PREPROCESSOR_
#define _PREPROCESSOR_

#include "TokenSource.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

typedef std::pair<TokenSource, std::string> Tline;

std::vector<Tline> preProcess(const std::string &code, int cnt, std::string FN);

#endif
