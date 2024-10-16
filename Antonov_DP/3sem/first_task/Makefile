all: a.out
	./a.out
intset.o: intset.cpp intset.h
	g++ -c intset.cpp
test.o: test.cpp intset.cpp
	g++ -c test.cpp
a.out: test.o intset.o
	g++ test.o intset.o
