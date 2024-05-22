all: a.out run

paragraph.o: paragraph.c paragraph.h
	gcc -c paragraph.c

main.o: main.c paragraph.h
	gcc -c main.c

run: a.out
	./a.out

a.out: main.o paragraph.o
	gcc main.o paragraph.o -lm