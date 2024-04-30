all: a.out run

findRoot.o: findRoot.c findRoot.h
	gcc -c findRoot.c

main.o: main.c findRoot.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o findRoot.o
	gcc main.o findRoot.o -lm
