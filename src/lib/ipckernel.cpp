/*
 * ipckernel.c
 *
 *  Created on: Mar 18, 2021
 *      Author: zbc
 */
#include "ipc/ipccxx/ipc.pb.h"
#include "types/aloipckernel.h"
#include "types/alostring.h"
#include <sys/stat.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <string>

int pipeid;

struct args {
    alostring name;
    long long addr;
};

std::string random_string()
{
    std::string str("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937       generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, 32); // assumes 32 < number of characters in str
}

extern "C" void string2char(int *data, long long length, char *dst);

extern "C" void __alolang__inner_ipckernel_compile(long long  kernel_addr,
                                                   long long  argCnt,
                                                   alostring *argsAddr,
                                                   alostring  str)
{
    std::string kernel_id = random_string();
    char        tbuff[256];

    std::cout << std::endl;
    alokernel *kernel = (alokernel *)kernel_addr;
    char       buff[str.data.size * 4 + 1];
    string2char((int *)str.data.pointer.addr, str.data.size, buff);
    std::ofstream client_file("ALOLANG_" + kernel_id + ".py", std::ios::out);
    if (!client_file.is_open()) {
        std::cout << "未成功打开文件" << std::endl;
    }
    client_file << "def alolang_run(alolang_var):" << std::endl;
    for (long long i = 0; i < argCnt; i++) {
        string2char((int *)argsAddr[i].data.pointer.addr, argsAddr[i].data.size,
                    tbuff);
        client_file << "    " << tbuff << "=alolang_var[\"" << tbuff << "\"]"
                    << std::endl;
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
    std::string pipeName = ".alolangpipe_" + kernel_id;
    master_file << "import "
                << "ALOLANG_" + kernel_id << " as client" << std::endl;
    master_file << master_source;
    master_file << std::endl << "listen(\"" << pipeName << "\")" << std::endl;
    master_file.close();
    mkfifo((pipeName + "_out").c_str(), 0666);
    mkfifo((pipeName + "_in").c_str(), 0666);
    if (0 == fork()) {
        execl("/bin/sh", "sh", "-c", "python ./master.py", (char *)0);
        _exit(127);
    } else {
        std::fstream *output = new std::fstream(
            pipeName + "_out",
            std::ios::out | std::ios::trunc | std::ios::binary);
        std::fstream *input =
            new std::fstream(pipeName + "_in", std::ios::in | std::ios::binary);
        kernel->outputaddr = (long long)output;
        kernel->inputaddr  = (long long)input;
    }
}

extern "C" void __alolang__inner_ipckernel_call(long long kernel_addr,
                                                long long argCnt,
                                                args *    argsAddr)
{
    alokernel *   kernel = (alokernel *)kernel_addr;
    std::fstream &output = *(std::fstream *)kernel->outputaddr;
    std::fstream &input  = *(std::fstream *)kernel->inputaddr;

    msg new_msg;
    new_msg.set_version(1);
    new_msg.set_command(1);
    char tbuff[256];

    for (long long i = 0; i < argCnt; i++) {
        string2char((int *)argsAddr[i].name.data.pointer.addr,
                    argsAddr[i].name.data.size, tbuff);
        msg::Data *varData = new_msg.add_data();
        varData->set_id(tbuff);
        long long value = *(long long *)argsAddr[i].addr;
        varData->set_dat(value);
    }
    std::string result = new_msg.SerializeAsString();
    int         len    = result.length();
    output.write(reinterpret_cast<const char *>(&len), sizeof(len));
    output << result;
    output.flush();
    input.read((char *)&len, sizeof(len));
    char buff[512];
    input.read(buff, len);
    new_msg.ParseFromString(buff);
    // google::protobuf::ShutdownProtobufLibrary();
}
