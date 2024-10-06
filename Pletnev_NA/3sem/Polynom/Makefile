all: a.out run

main.o: main.cpp Polynom.hpp
	gcc -c main.cpp

run: a.out
	./a.out

a.out: main.o
	gcc main.o -lm