// compileerror.hpp header for CompileError exeption class
#ifndef _COMPILE_ERROR_
#define _COMPILE_ERROR_
#include <exception>
#include <string>

class CompileError : public std::exception
{
  private:
    std::string error;
    std::string message;
    std::string file;
    uint64_t    line;

  public:
    const char *what() const throw() { return message.c_str(); }
    CompileError(const char *whatError, std::string whatFile = "",
                 uint64_t whatLine = 0)
    {
        error   = whatError;
        file    = whatFile;
        line    = whatLine;
        message = file + ": " + std::to_string(line) + ": " + error;
    }
    CompileError(const std::string &whatError, std::string whatFile = "",
                 uint64_t whatLine = 0)
    {
        error   = whatError;
        file    = whatFile;
        line    = whatLine;
        message = file + ":" + std::to_string(line) + ": " + error;
    }
};
#endif
