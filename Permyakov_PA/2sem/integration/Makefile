all: a.out run

findRoot.o: DetInt.c DetInt.h
	gcc -c DetInt.c

main.o: main.c DetInt.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o DetInt.o
	gcc main.o DetInt.o -lm

