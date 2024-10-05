all: a.out
	./a.out
test.o: test.cpp Head.h
	g++ -c test.cpp
a.out: test.o
	g++ test.o
