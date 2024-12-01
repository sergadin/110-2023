CXX = g++
CXXFL = -Wall -Werror

all: run clear

run: a.out
	./a.out
	gnuplot -persist script.gp

a.out: point.o line.o polygon.o main.o
	g++ $(CXXFL) -c point.cpp
	g++ $(CXXFL) -c line.cpp
	g++ $(CXXFL) -c polygon.cpp
	g++ $(CXXFL) -c main.cpp
	g++ point.o line.o polygon.o main.o -lm
	
clear:
	rm point.o line.o polygon.o main.o a.out pic.png
