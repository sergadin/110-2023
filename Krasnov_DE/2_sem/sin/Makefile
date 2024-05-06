all: a.out run

core.o: core.c sin.h
	gcc -c core.c

main.o: main.c sin.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o core.o
	gcc main.o core.o -lm


