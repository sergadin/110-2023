all : a.out run



rank.o : rank.c rank.h

	gcc -c -g rank.c



main.o : main.c rank.h

	gcc -c -g main.c

run : a.out

	./a.out



a.out : main.o rank.o

	gcc -g main.o rank.o -lm
