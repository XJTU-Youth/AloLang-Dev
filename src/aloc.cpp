#include "CompileError.hpp"
#include "CompileUnit.h"
#include "preprocessor.h"
#include "utils.h"
#include <boost/program_options.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>

int opt;

std::ifstream fin;
std::ofstream fout;

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace po = boost::program_options;

std::vector<string> input_file_names;
std::string         output_file_name;
std::string         alolanglibdir;

int main(int argc, char *argv[])
{
    try {
        // Declare a group of options that will be
        // allowed only on command line
        po::options_description generic("Generic options");
        generic.add_options()("version,v", "print version string")(
            "help", "produce help message")("static",
                                            "Build static linked executable");

        // Declare a group of options that will be
        // allowed both on command line and in
        // config file
        po::options_description config("Configuration");
        config.add_options()("output,o", po::value<string>(), "output file");
        config.add_options()(
            "alolanglib,L", po::value<string>(),
            "Alolang Core Library Position, default to src/lib");

        // Hidden options, will be allowed both on command line and
        // in config file, but will not be shown to the user.
        po::options_description hidden("Hidden options");
        hidden.add_options()("input-file", po::value<vector<string>>(),
                             "input file");
        po::options_description cmdline_options;
        cmdline_options.add(generic).add(config).add(hidden);

        po::options_description visible("Allowed options");
        visible.add(generic).add(config);

        po::positional_options_description p;
        p.add("input-file", -1);

        po::variables_map vm;
        store(po::command_line_parser(argc, argv)
                  .options(cmdline_options)
                  .positional(p)
                  .run(),
              vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << "Usage: " << argv[0] << " [options] input-files\n";
            cout << visible << "\n";
            return 0;
        }

        if (vm.count("version")) {
            cout << "AloLang compiler, pre-dev version\n";
            return 0;
        }

        if (vm.count("input-file")) {
            input_file_names = vm["input-file"].as<std::vector<std::string>>();

            if (vm.count("alolanglib"))
                alolanglibdir = vm["alolanglib"].as<std::string>();
            else
                output_file_name = "src/lib";

            for (std::string input_file_name : input_file_names) {
                if (vm.count("output"))
                    output_file_name = vm["output"].as<std::string>();
                else
                    output_file_name = "a.out";
                fin.open(input_file_name);
                if (!fin.is_open()) {
                    cerr << argv[0]
                         << ": fatal error: file not found\ncompilation "
                            "terminated\n";
                    return 1;
                }
                std::string buff; //源码
                std::getline(fin, buff, char(EOF));
                std::vector<Tline> preProcessed;
                fin.close();
                // std::string header = "%import types\n";
                // buff = header + buff;
                try {
                    preProcessed = preProcess(buff, 0, input_file_name);
                    for (Tline line : preProcessed) {
                        std::cout << line.second << std::endl;
                    }
                    // todo:这行代码写的极不规范，尽快修改
                    CompileUnit(input_file_name, preProcessed).compile();
                    system(("llc ./" + input_file_name +
                            ".bc --relocation-model=pic")
                               .c_str());
                    system(("llvm-dis ./" + input_file_name + ".bc").c_str());

                } catch (const CompileError &e) {
                    cerr << "Compile Error: " << e.what() << endl
                         << "Compilation Terminated\n";
                    return 1;
                }
            }
            //下面代码仅用来方便调试
            std::string objs = " ";
            for (std::string input_file_name : input_file_names) {
                objs += "./" + input_file_name + ".s ";
            }
            std::string cmdline = "g++ -O0" + objs +
                                  (vm.count("static") ? "-static " : "") +
                                  " -fPIE -L " + alolanglibdir +
                                  " -l m -l stdc++ -l alolangcore -std=c++17" +
                                  " -o " + output_file_name;
            std::cout << "debug info:" << cmdline << std::endl;
            system(cmdline.c_str());
            return 0;
        } else {
            cout << "Usage: " << argv[0] << " [options] input-files\n";
            cout << visible << "\n";
            return 1;
        }
    } catch (std::exception &e) {
        cout << "Exception: " << e.what() << endl;
        return 1;
    }
}
