/*
 * ipckernel.c
 *
 *  Created on: Mar 18, 2021
 *      Author: zbc
 */
#include "types/alostring.h"
#include <sys/stat.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

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
    system("cp src/lib/ipc/ipcpy/ipc_pb2.py ./ipc_pb2.py");
    std::string   master_source; // master源码
    std::ifstream fin;
    fin.open("src/lib/ipc/ipcpy/master.py");
    if (!fin.is_open()) {
        std::cout << "未成功打开文件master文件" << std::endl;
    }
    std::getline(fin, master_source, char(EOF));
    fin.close();
    std::ofstream master_file("master.py", std::ios::out);
    if (!master_file.is_open()) {
        std::cout << "未成功打开master文件" << std::endl;
    }
    master_file << master_source;
    master_file << std::endl
                << "listen(\""
                << "test_pipe"
                << "\")" << std::endl;
    master_file.close();
    const char *fifo_name = "test_pipe";
    mkfifo(fifo_name, 0666);
    if (0 == fork()) {
        execl("/bin/sh", "sh", "-c", "python ./master.py", (char *)0);
        _exit(127);
    } else {
    }
}
