all: a.out run 

main.o: main.cpp BasicTree.h
	g++ -c main.cpp
    
run: a.out
	valgrind ./a.out
    
a.out: main.o
	g++ main.o -lm
