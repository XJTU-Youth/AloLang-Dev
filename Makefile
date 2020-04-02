aloc: compiler/cppfront.cpp
	g++ -o aloc compiler/cppfront.cpp

.PHONY : clean
clean:
	rm aloc