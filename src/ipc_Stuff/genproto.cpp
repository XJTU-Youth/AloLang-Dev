#include "genproto.h"
#include <boost/format.hpp>
#include <map>

std::map<std::string, std::string> alot_to_protot{{"int", "int64"},
                                                  {"double", "double"},
                                                  {"char", "int32"},
                                                  {"byte", "int32"},
                                                  {"pointer", "uint64"}};

proto::proto()
{
    this->protostr = "";
    this->protostr +=
        R"(syntax = "proto3";
    )";
}

void proto::addType(std::string              typenamestr,
                    std::vector<std::string> membertype)
{
    std::string typeMsg = "";
    typeMsg += (boost::format("message %1%\n") % typenamestr).str();
    typeMsg += "{\n";
    int li = 1;
    for (auto mbs : membertype) {
        auto tn = alot_to_protot.find(mbs) != alot_to_protot.end()
                      ? alot_to_protot[mbs]
                      : mbs;
        typeMsg +=
            (boost::format("    %1% %2%_%3% = %3%;\n") % tn % mbs % li).str();
        li++;
    }
    typeMsg += "}\n";
    this->protostr += typeMsg += "\n";
}