all: a.out run

findRoot.o: CalcTan.c CalcTan.h
	gcc -c CalcTan.c

main.o: main.c CalcTan.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o CalcTan.o
	gcc main.o CalcTan.o -lm

