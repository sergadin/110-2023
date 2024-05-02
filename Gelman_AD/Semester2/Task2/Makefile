all: a.out run

root.o: root.c root.h
	gcc -c root.c

main.o: main.c root.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o root.o
	gcc main.o root.o -lm