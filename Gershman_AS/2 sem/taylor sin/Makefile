all: a.out run

taylor_sin.o: taylor_sin.c taylor_sin.h
	gcc -c taylor_sin.c

main.o: main.c taylor_sin.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o taylor_sin.o
	gcc main.o taylor_sin.o -lm