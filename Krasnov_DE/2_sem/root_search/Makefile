all: a.out run

core.o: core.c root_search.h
	gcc -c core.c

main.o: main.c root_search.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o core.o
	gcc main.o core.o -lm


