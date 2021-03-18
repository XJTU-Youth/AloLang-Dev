/*
 * alostring.h
 *
 *  Created on: Mar 18, 2021
 *      Author: zbc
 */

#ifndef SRC_LIB_TYPES_ALOSTRING_H_
#define SRC_LIB_TYPES_ALOSTRING_H_

struct aloptr {
    long long addr;
};
struct aloarray_char {
    struct aloptr pointer;
    long long     size;
};
struct alostring {
    struct aloarray_char data;
};

#endif /* SRC_LIB_TYPES_ALOSTRING_H_ */
