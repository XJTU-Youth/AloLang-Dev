/*
 * utils.h
 *
 *  Created on: May 2, 2020
 *      Author: zbc
 */

#ifndef COMPILER_UTILS_H_
#define COMPILER_UTILS_H_

#include <ast/TypeAST.h>
#include <sstream>
#include <vector>

std::string demangle(const std::string &           fnName,
                     const std::vector<TypeAST *> &argTypes,
                     const std::string &           className = "");

bool isSyntax(char c);
void skipSpace(const std::vector<std::string> &words, long unsigned int &i);
void skipSpace(std::istream &in);

template <typename Base, typename T> inline bool instanceof (const T *)
{
    return std::is_base_of<Base, T>::value;
}
#endif /* COMPILER_UTILS_H_ */
