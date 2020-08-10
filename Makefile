CC = g++
AR = ar  

CFLAG = -W -Wall -g

AST_SRCS := $(wildcard compiler/ast/*.cpp)
AST_OBJS := $(AST_SRCS:.cpp=.o)
AST_OBJS_BUILD := $(addprefix build/,${AST_OBJS})
OBJ_DIR = build/

aloc: build/compiler/cppfront.o build/compiler/preprocessor.o build/compiler/utils.o $(AST_OBJS_BUILD)
	$(CC) $(CFLAG) build/compiler/cppfront.o build/compiler/preprocessor.o build/compiler/utils.o $(AST_OBJS_BUILD) -lLLVM -o aloc 

build/compiler/preprocessor.o: compiler/preprocessor.cpp compiler/preprocessor.hpp compiler/compileerror.hpp
	$(CC) $(CFLAG) -c -I ./compiler/ compiler/preprocessor.cpp -o build/compiler/preprocessor.o

build/compiler/cppfront.o: compiler/cppfront.cpp compiler/preprocessor.hpp compiler/compileerror.hpp
	$(CC) $(CFLAG) -c -I ./compiler/ compiler/cppfront.cpp -o build/compiler/cppfront.o
	
build/compiler/utils.o: compiler/utils.cpp
	$(CC) $(CFLAG) -c -I ./compiler/ compiler/utils.cpp -o build/compiler/utils.o

$(AST_OBJS_BUILD):$(OBJ_DIR)%.o : %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ 

.PHONY : clean,install
install: aloc
	mv aloc /usr/bin/
clean:
	-rm aloc build/compiler/*.o build/compiler/ast/*.o 
