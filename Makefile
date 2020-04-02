aloc: compiler/cppfront.cpp
	g++ -o aloc compiler/cppfront.cpp

.PHONY : clean,install
install: aloc
	mv aloc /usr/bin/
clean:
	-rm aloc
