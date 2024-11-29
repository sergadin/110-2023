all: a.out
	valgrind ./a.out
triangle.o: triangle.cpp triangle.h max_area.cpp
	g++ -c triangle.cpp max_area.cpp
test.o: test.cpp triangle.cpp max_area.cpp
	g++ -c test.cpp
a.out: test.o triangle.o max_area.o
	g++ test.o triangle.o max_area.o
