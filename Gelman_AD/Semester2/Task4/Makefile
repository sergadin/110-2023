all: a.out
	./a.out
minvalue.o: minvalue.c minvalue.h
	gcc -c minfalue.c

main.o: main.c minvalue.h
	gcc -c main.c

a.out: main.o minvalue.o
	gcc main.o minvalue.o