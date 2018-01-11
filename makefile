all: Line.o nono.o
	g++ -std=c++11 nono.o Line.o
Line.o: Line.cpp
	g++ -std=c++11 -c Line.cpp
nono.o: nono.cpp
	g++ -std=c++11 -c nono.cpp
clean: 
	rm a.exe nono.o Line.o