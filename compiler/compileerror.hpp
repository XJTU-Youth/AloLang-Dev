// compileerror.hpp header for CompileError exeption class
#ifndef _COMPILE_ERROR_
#define _COMPILE_ERROR_
#include <string>
#include <exception>

class CompileError: public std::exception {
private:
	std::string error;
public:
	const char *what() const throw()
	{
		return error.c_str();
	}
	CompileError(const char *whatError)
	{
		error = whatError;
	}
};
#endif
