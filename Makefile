aloc: compiler/cppfront.cpp
	g++ -o aloc compiler/cppfront.cpp -g

.PHONY : clean,install
install: aloc
	mv aloc /usr/bin/
clean:
	-rm aloc
