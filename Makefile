aloc: compiler/cppfront.cpp compiler/compileerror.hpp
	g++ -o aloc compiler/cppfront.cpp -g

.PHONY : clean,install
install: aloc
	mv aloc /usr/bin/
clean:
	-rm aloc
