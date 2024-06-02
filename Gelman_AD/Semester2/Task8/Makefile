all: a.out run

gauss.o: gauss.c gauss.h
	gcc -c gauss.c

main.o: main.c gauss.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o gauss.o
	gcc main.o gauss.o -lm