// compileerror.hpp header for CompileError exeption class
#ifndef _COMPILE_ERROR_
#define _COMPILE_ERROR_
#include "TokenSource.h"
#include <exception>
#include <string>

class CompileError : public std::exception
{
  private:
    std::string error;
    std::string message;
    TokenSource source;

  public:
    const char *what() const throw() { return message.c_str(); }
    CompileError(const char *whatError,
                 TokenSource source = TokenSource("<unknown>", 0))
    {
        error        = whatError;
        this->source = source;
        message =
            source.file + ":" + std::to_string(source.lineno) + ": " + error;
    }

    CompileError(const std::string &whatError,
                 TokenSource        source = TokenSource("<unknown>", 0))
    {
        error        = whatError;
        this->source = source;
        message =
            source.file + ":" + std::to_string(source.lineno) + ": " + error;
    }
};
#endif
