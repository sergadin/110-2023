all: a.out
	./a.out
polynom.o: polynom.cpp polynom.h
	g++ -c polynom.cpp
test.o: test.cpp polynom.cpp
	g++ -c test.cpp
a.out: test.o polynom.o
	g++ test.o polynom.o
