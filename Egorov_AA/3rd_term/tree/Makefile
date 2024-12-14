CXX = g++
CXXFL = -Wall -Werror

all: run clear

run: a.out
	valgrind ./a.out

a.out: main.o
	g++ $(CXXFL) -c main.cpp
	g++ main.o -lm
	
clear:
	rm main.o a.out 
