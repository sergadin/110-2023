all: a.out run

calculateSin.o: calculateSin.c calculateSin.h
	gcc -c calculateSin.c

main.o: main.c calculateSin.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o calculateSin.o
	gcc main.o calculateSin.o -lm
