all: a.out run

core.o: core.c fill_massiv.h
	gcc -c -g core.c

main.o: main.c fill_massiv.h
	gcc -c -g main.c

run: a.out
	./a.out

a.out: main.o core.o
	gcc main.o core.o -lm


