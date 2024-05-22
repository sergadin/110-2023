all: a.out run

polygon.o: polygon.c polygon.h
	gcc -c polygon.c

main.o: main.c polygon.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o polygon.o
	gcc main.o polygon.o -lm