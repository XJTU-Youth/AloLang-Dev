AUTOMAKE_OPTIONS = foreign subdir-objects
bin_PROGRAMS = aloc
aloc_SOURCES = aloc.cpp CompileUnit.cpp Preprocessor.cpp Token.cpp utils.cpp\
    ast/BaseAST.cpp ast/BinaryExprAST.cpp ast/BoolExprAST.cpp\
    ast/CallExprAST.cpp ast/ClassAST.cpp ast/CodeBlockAST.cpp ast/DoubleExprAST.cpp ast/EmptyExprAST.cpp\
    ast/ExprAST.cpp ast/ExternAST.cpp ast/FunctionAST.cpp ast/KernelCallExprAST.cpp ast/KernelCompileExprAST.cpp\
    ast/IntExprAST.cpp ast/IfExprAST.cpp ast/MemberExprAST.cpp ast/PrototypeAST.cpp\
    ast/ReturnExprAST.cpp ast/SizeofExprAST.cpp ast/StringExprAST.cpp ast/TypeAST.cpp ast/VariableDefExprAST.cpp ast/VariableExprAST.cpp\
    ast/WhileExprAST.cpp ast/UnaryExprAST.cpp yacc_stuff/tokenizer.lpp

AM_LFLAGS = -o lex.yy.c

ldflagsLLVM := $(shell llvm-config --ldflags)
cxxflagsLLVM := $(shell llvm-config --cxxflags)
libLLVM := $(shell llvm-config --libs)
includeLLVM := $(shell llvm-config --includedir)

aloc_CPPFLAGS = $(cxxflagsLLVM) -I$(includeLLVM) -I$(srcdir) -fexceptions
aloc_LDFLAGS = $(ldflagsLLVM) #$(libLLVM) -lboost_program_options
aloc_LDADD = -lLLVM-11 -lboost_program_options -lboost_filesystem -lboost_system