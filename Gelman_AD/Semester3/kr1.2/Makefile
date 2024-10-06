all: a.out
	./a.out
polynom.o: polynom.cpp polynom.h
	g++ -c polynom.cpp
a.out: polynom.o
	g++ polynom.o