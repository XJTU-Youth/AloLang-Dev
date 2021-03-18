/*
 * Preprocessor.h
 *
 *  Created on: Mar 18, 2021
 *      Author: zbc
 */

#ifndef SRC_PREPROCESSOR_H_
#define SRC_PREPROCESSOR_H_

#include "TokenSource.h"
#include <fstream>
#include <map>
#include <string>
#include <vector>

class CompileUnit;
class Preprocessor
{
  public:
    Preprocessor(CompileUnit *unit);
    virtual ~Preprocessor();

    std::vector<Tline> process();
    std::vector<Tline> processPreInstruction(const std::string &line, int cnt,
                                             int lineno, const std::string &FN);

    std::string        findRealData(std::string &key);
    std::string        doReplace(std::string &line);
    std::vector<Tline> preProcess(const std::string &code, int cnt,
                                  std::string FN);
    CompileUnit *      unit;
    std::string        osrc;
    std::ifstream      t_fin__;

    std::map<std::string, std::string> variable;
    int                                closeifstack   = 0;
    int                                currentifstack = 0;
};

#endif /* SRC_PREPROCESSOR_H_ */
