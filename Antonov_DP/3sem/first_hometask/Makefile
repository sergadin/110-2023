all: a.out
	./a.out
triangle.o: triangle.cpp triangle.h
	g++ -c triangle.cpp
test.o: test.cpp triangle.cpp
	g++ -c test.cpp
a.out: test.o triangle.o
	g++ test.o triangle.o
