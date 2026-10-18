all: a.out
	./a.out
local_clock.o: local_clock.cpp local_clock.h
	g++ -c local_clock.cpp
test.o: test.cpp local_clock.cpp
	g++ -c test.cpp
a.out: test.o local_clock.o
	g++ test.o local_clock.o
