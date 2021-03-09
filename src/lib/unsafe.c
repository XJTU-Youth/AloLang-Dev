/*
 * unsafe.c
 *
 *  Created on: Mar 7, 2021
 *      Author: zbc
 */
#include <stdlib.h>

extern void _alolang_7__cfree3inte(long long addr) { free((void *)addr); }

struct addr {
    long long addr;
};

extern struct addr _alolang_9__cmalloc3inte(long long size)
{
    struct addr retValue;
    retValue.addr = (long long)malloc(size);
    return retValue;
}
