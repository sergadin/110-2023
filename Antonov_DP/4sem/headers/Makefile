all: a.out
	./a.out
test.o: test.cpp
	g++ -c test.cpp
a.out: test.o
	g++ test.o
