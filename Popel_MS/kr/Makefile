all: do-test clear

do-test: a.out
	valgrind --track-origins=yes -s ./a.out

a.out: intset.o main.o
	g++ -c intset.cpp
	g++ -c main.cpp
	g++ intset.o main.o -lm

clear:
	rm intset.o main.o a.out


