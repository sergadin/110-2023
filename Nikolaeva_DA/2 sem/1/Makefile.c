all: a.out run
sem2.o : sem2.c sem2.h
         gcc -c sem2.c

	
main.o : main.c sem2.h
         gcc -c main.c


run : a.out
        ./a.out


a.out : main.o sem2.o
        gcc main.o sem2.o -lm
