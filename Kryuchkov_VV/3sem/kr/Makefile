all: do-test clear

do-test: a.out
	valgrind --track-origins=yes -s ./a.out

a.out: vector.o main.o
	g++ -c vector.cpp
	g++ -c main.cpp
	g++ vector.o main.o -lm

clear:
	rm vector.o main.o a.out


