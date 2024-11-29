all: a.out
	./a.out
restaurant.o: restaurant.cpp restaurant.h
	g++ -c restaurant.cpp
test.o: test.cpp restaurant.cpp
	g++ -c test.cpp
a.out: test.o restaurant.o
	g++ test.o restaurant.o
