all: a.out run

core.o: core.c speedy_descent.h
	gcc -c -g core.c

main.o: main.c speedy_descent.h
	gcc -c -g main.c

run: a.out
	./a.out

a.out: main.o core.o
	gcc main.o core.o -lm
