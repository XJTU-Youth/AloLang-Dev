aloc: compiler/cppfront.o compiler/preprocessor.o 
	g++ -g -o aloc compiler/cppfront.o compiler/preprocessor.o

compiler/preprocessor.o: compiler/preprocessor.cpp compiler/preprocessor.hpp compiler/compileerror.hpp
	g++ -g -c -I ./compiler/ compiler/preprocessor.cpp -o compiler/preprocessor.o

compiler/cppfront.o: compiler/cppfront.cpp compiler/preprocessor.hpp compiler/compileerror.hpp
	g++ -g -c -I ./compiler/ compiler/cppfront.cpp -o compiler/cppfront.o

.PHONY : clean,install
install: aloc
	mv aloc /usr/bin/
clean:
	-rm aloc compiler/*.o 
