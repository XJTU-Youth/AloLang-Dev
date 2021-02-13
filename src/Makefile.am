AUTOMAKE_OPTIONS = foreign subdir-objects
bin_PROGRAMS = aloc
aloc_SOURCES = aloc.cpp CompileUnit.cpp preprocessor.cpp Token.cpp utils.cpp\
    ast/BaseAST.cpp ast/CallExprAST.cpp ast/CodeBlockAST.cpp ast/ExprAST.cpp\
    ast/ExternAST.cpp ast/FunctionAST.cpp ast/IntExprAST.cpp ast/PrototypeAST.cpp\
    ast/VariableExprAST.cpp yacc_stuff/lex.yy.cc

ldflagsLLVM := $(shell llvm-config --ldflags)
cxxflagsLLVM := $(shell llvm-config --cxxflags)
libLLVM := $(shell llvm-config --libs)
includeLLVM := $(shell llvm-config --includedir)

aloc_CPPFLAGS = $(cxxflagsLLVM) -I$(includeLLVM) -I$(srcdir) -fexceptions
aloc_LDFLAGS = $(ldflagsLLVM) $(libLLVM) -lboost_program_options
