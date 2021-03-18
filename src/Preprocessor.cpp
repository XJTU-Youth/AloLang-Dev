/*
 * Preprocessor.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: zbc
 */

#include "Preprocessor.h"

#include "CompileUnit.h"
#include "boost/filesystem.hpp"
#include "utils.h"
#include <CompileError.hpp>
#include <vector>

std::pair<std::string, std::string> genFactor(const std::string &line)
{
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
        return std::pair<std::string, std::string>(
            line.substr(1, i - 1), line.substr(i + 1, len - i - 1));
    }
}

Preprocessor::Preprocessor(CompileUnit *unit) { this->unit = unit; }

Preprocessor::~Preprocessor()
{
    // TODO Auto-generated destructor stub
}

std::vector<Tline> Preprocessor::process()
{
    std::string   buff; //源码
    std::ifstream fin;
    fin.open(unit->name);
    if (!fin.is_open()) {
        throw new CompileError("file " + unit->name + " not found");
    }
    std::getline(fin, buff, char(EOF));
    fin.close();

    std::vector<Tline> preProcessed;
    preProcessed = preProcess(buff, 0, unit->name);
    return preProcessed;
}

std::vector<Tline> Preprocessor::processPreInstruction(const std::string &line,
                                                       int cnt, int lineno,
                                                       const std::string &FN)
{
    boost::filesystem::path             curFile(FN);
    std::pair<std::string, std::string> instruction =
        genFactor(line); //解析后的预编译指令
    if (instruction.first == "import") {
        std::string realPath =
            curFile.parent_path().string() + "/" + instruction.second;
        std::ifstream t_fin__;
        t_fin__.open(realPath);
        if (!t_fin__.is_open()) {
            CompileError e("import file " + realPath + " not found",
                           TokenSource(FN, lineno));
            throw e;
        }
        std::string importFileContent;
        std::getline(t_fin__, importFileContent, char(EOF));
        t_fin__.close();
        return preProcess(importFileContent, cnt + 1, realPath);
    } else if (instruction.first == "def") {
        //解析宏定义
        std::string var, data;
        int         len = instruction.second.length();
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
            var  = instruction.second.substr(0, len);
            data = "";
        } else {
            var  = instruction.second.substr(0, i);
            data = instruction.second.substr(i + 1, len - i - 1);
        }
        variable[var] = data;
        return std::vector<Tline>{Tline(TokenSource("", lineno), "")};
    } else if (instruction.first == "rmdef") {
        if (instruction.second.length() == 0) {
            CompileError e("no second instruction");
            throw e;
        }
        if (!variable.erase(instruction.second)) {
            CompileError e("removing macro " + instruction.second +
                           " that doent exist");
            throw e;
            //找不到宏定义
        }
        return std::vector<Tline>{Tline(TokenSource("", lineno), "")};
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
        return std::vector<Tline>{Tline(TokenSource("", lineno), "")};
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
        return std::vector<Tline>{Tline(TokenSource("", lineno), "")};
    } else if (instruction.first == "endif") {
        if (currentifstack == 0) {
            CompileError e("no second instruction");
            throw e;
        }
        if (closeifstack > 0) {
            closeifstack--;
        }
        currentifstack--;
        return std::vector<Tline>{Tline(TokenSource("", lineno), "")};
    } else {
        CompileError e("Unrecognized preprocessor command " +
                       instruction.first);
        throw e;
    }
}

std::string Preprocessor::findRealData(std::string &key)
{
    std::map<std::string, std::string>::iterator iter = variable.find(key);
    if (iter != variable.end()) {
        return findRealData(iter->second);
    } else {
        return key;
    }
}

//宏替换
std::string Preprocessor::doReplace(std::string &line)
{
    std::vector<std::string> words;
    bool                     flag = false; //判断栈顶元素状态
    for (long unsigned int i = 0; i < line.length(); i++) {
        if (isSyntax(line[i])) {
            words.push_back(std::string(1, line[i]));
            flag = false;
        } else {
            if (!flag) {
                words.push_back(std::string(1, line[i]));
                flag = true;
            } else {
                words[words.size() - 1] += std::string(1, line[i]);
            }
        }
    }
    std::stringstream ss;
    for (std::string tmp : words) {
        ss << findRealData(tmp);
    }
    return ss.str();
}

//递归预处理
std::vector<Tline> Preprocessor::preProcess(const std::string &code, int cnt,
                                            std::string FN)
{
    if (cnt == 128) {
        CompileError e("preprocessor recursion too deep");
        throw e;
    }
    std::istringstream buft_fin__(code);
    std::vector<Tline> processedLines;
    std::string        temp;
    bool               isCommented    = false;
    int                lineno         = 0;
    bool               raw_string     = false;
    std::string        tmp_raw_string = "";
    while (std::getline(buft_fin__, temp)) {
        lineno++;
        if (raw_string) {
            long unsigned int position = temp.find("\"\"\"\"");
            if (position != temp.npos) {
                tmp_raw_string += tmp_raw_string.substr(0, position);
                temp       = temp.substr(position + 4);
                raw_string = false;
                processedLines.push_back(Tline(TokenSource(FN, lineno),
                                               "\"" + tmp_raw_string + "\""));
                tmp_raw_string = "";
            } else {
                tmp_raw_string = tmp_raw_string + temp + "\\n";
                continue;
            }
        }
        if (closeifstack > 0 && temp.substr(0, 6) != "%endif" &&
            temp.substr(0, 7) != "%ifndef" && temp.substr(0, 6) != "%ifdef") {
            continue;
        }

        if (temp[0] == '%') {
            auto processedPreInstruction =
                processPreInstruction(temp, cnt, lineno, FN);
            if (processedPreInstruction.size() > 0)
                std::move(processedPreInstruction.begin(),
                          processedPreInstruction.end(),
                          std::back_inserter(processedLines));
        } else {
            std::string replaced = doReplace(temp);
            //处理块注释
            std::string result = "";

            //处理行注释
            bool              flag     = false;
            std::string       resulta  = replaced;
            long unsigned int position = replaced.find("//");
            if (position != replaced.npos) {
                resulta = replaced.substr(0, position);
            }
            position = resulta.find("/*");
            if (position != resulta.npos) {
                result += resulta.substr(0, position);
                isCommented = true;
                flag        = true;
            }

            position = resulta.find("*/");
            if (position != resulta.npos) {
                if (!isCommented) {
                    CompileError e("Haven't been commented");
                    throw e;
                }
                result += resulta.substr(position + 2,
                                         resulta.length() - position - 2);
                isCommented = false;
                flag        = true;
            }
            if (!flag) {
                result = resulta;
            }
            if (isCommented) {
                result = "";
            }

            position = result.find("\"\"\"\"");
            if (position != temp.npos) {
                tmp_raw_string = result.substr(position + 4);
                result         = result.substr(0, position);
                raw_string     = true;
            }
            int plen = result.length();
            if (plen > 0) {
                processedLines.push_back(
                    Tline(TokenSource(FN, lineno), result));
            }
        }
        temp.erase();
    }
    return processedLines;
}
