all: a.out run

strings.o: strings.c strings.h
	gcc -c strings.c

main.o: main.c strings.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o strings.o
	gcc main.o strings.o -lm