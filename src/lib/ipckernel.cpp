/*
 * ipckernel.c
 *
 *  Created on: Mar 18, 2021
 *      Author: zbc
 */
#include "types/alostring.h"

#include <fstream>
#include <iostream>

extern "C" void string2char(int *data, long long length, char *dst);

extern "C" void __alolang__inner_ipckernel_compile(alostring str)
{
    char buff[str.data.size * 4 + 1];
    string2char((int *)str.data.pointer.addr, str.data.size, buff);
    std::ofstream client_file("client.py", std::ios::out);
    if (!client_file.is_open()) {
        std::cout << "未成功打开文件" << std::endl;
    }
    client_file << buff;
    client_file.close();
    system("python ./client.py");
}
