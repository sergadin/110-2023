CC = gcc
CFLAGS = -g -Wall -Wextra -Wfloat-equal -Werror -std=c99 -pedantic

all: a.out

iter.o: iter.c iter.h
	$(CC) $(CFLAGS) -c iter.c -o iter.o

main.o: main.c iter.h
	$(CC) $(CFLAGS) -c main.c -o main.o

a.out: main.o iter.o
	$(CC) $(CFLAGS) main.o iter.o -o a.out -lm

run: a.out
	valgrind ./a.out
