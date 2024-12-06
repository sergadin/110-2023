all: a.out
	./a.out
rectangle.o: rectangle.cpp rectangle.h
	g++ -c rectangle.cpp
test.o: test.cpp rectangle.cpp
	g++ -c test.cpp
a.out: test.o rectangle.o
	g++ test.o rectangle.o
