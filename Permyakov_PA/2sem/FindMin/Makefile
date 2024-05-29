all: a.out run

findRoot.o: FindMin.c FindMin.h
	gcc -c FindMin.c

main.o: main.c FindMin.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o FindMin.o
	gcc main.o FindMin.o -lm

