#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_CONFIG_MACRO_DIR([m4])
AC_PREREQ([2.69])
AC_INIT([AloLang Compiler], [Dev Beta], [https://github.com/XJTU-Youth/AloLang-Dev/issues])

AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug],[debug program(default is no)])],
    [CFLAGS="${CFLAGS} -g -O0"],
    [CFLAGS="-g -O2"])

AC_CONFIG_SRCDIR([src/aloc.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LEX(noyywrap)
AC_PROG_RANLIB
# Checks for libraries.
# FIXME: Replace 'main' with a function in '-lboost_program_options':
AC_CHECK_LIB([boost_program_options], [boost::program_options::strip_prefixes])
AC_CHECK_LIB([LLVM-11], [llvm::demangle])




# Checks for header files.
AC_CHECK_HEADERS([inttypes.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset strtol])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/lib/Makefile
])

AX_CXX_COMPILE_STDCXX(17, [noext], [mandatory])

AM_INIT_AUTOMAKE
AC_OUTPUT
