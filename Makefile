aloc: compiler/cppfront.o compiler/preprocessor.o compiler/utils.o compiler/ast.o
	g++ -g -o aloc compiler/cppfront.o compiler/preprocessor.o compiler/utils.o compiler/ast.o

compiler/preprocessor.o: compiler/preprocessor.cpp compiler/preprocessor.hpp compiler/compileerror.hpp
	g++ -g -c -I ./compiler/ compiler/preprocessor.cpp -o compiler/preprocessor.o

compiler/cppfront.o: compiler/cppfront.cpp compiler/preprocessor.hpp compiler/compileerror.hpp
	g++ -g -c -I ./compiler/ compiler/cppfront.cpp -o compiler/cppfront.o
	
compiler/utils.o: compiler/utils.cpp
	g++ -g -c -I ./compiler/ compiler/utils.cpp -o compiler/utils.o

compiler/ast.o: compiler/ast/AST_Base.cpp compiler/ast/AST_Expr.cpp
	g++ -g -c -I ./compiler/ ./compiler/ast/AST_Base.cpp ./compiler/ast/AST_Expr.cpp -o compiler/ast.o


.PHONY : clean,install
install: aloc
	mv aloc /usr/bin/
clean:
	-rm aloc compiler/*.o 
