all: do-test clear

do-test: a.out
	valgrind --track-origins=yes -s ./a.out

a.out: clock.o main.o
	g++ -c clock.cpp
	g++ -c main.cpp
	g++ clock.o main.o -lm

clear:
	rm clock.o main.o a.out


