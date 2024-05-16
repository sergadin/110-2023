all: a.out run

log.o: log.c log.h
	gcc -c log.c

main.o: main.c log.h
	gcc -c log.c

run: a.out
	./a.out

a.out: main.o log.o
	gcc main.o log.o - lm