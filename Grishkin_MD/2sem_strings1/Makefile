all : a.out run



strings.o : strings.c strings.h

	gcc -c -g strings.c



main.o : main.c strings.h

	gcc -c -g main.c

run : a.out

	./a.out



a.out : main.o strings.o

	gcc -g main.o strings.o -lm
