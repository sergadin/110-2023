CXX = g++
CXXFL = -Wall -Werror

all: run clear

run: a.out
	valgrind --track-origins=yes --leak-check=full -s ./a.out

a.out: btree.o main.o
	g++ $(CXXFL) -c btree.cpp
	g++ $(CXXFL) -c main.cpp
	g++ btree.o main.o -lm

clear:
	rm btree.o main.o a.out
