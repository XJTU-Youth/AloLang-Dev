/*
 * TokenSource.h
 *
 *  Created on: Mar 10, 2021
 *      Author: zbc
 */

#ifndef SRC_TOKENSOURCE_H_
#define SRC_TOKENSOURCE_H_

#include <string>

struct TokenSource {
    std::string file;
    uint64_t    lineno;
    TokenSource(std::string file, uint64_t lineno) : file(file), lineno(lineno)
    {
    }
    TokenSource() : file("<unknown>"), lineno(0) {}
};

#endif /* SRC_TOKENSOURCE_H_ */
