all : a.out run

matr.o : matr.c matr.h
	gcc -g -Wall -Wextra -Wfloat-equal -Werror -std=c99 -pedantic -c matr.c 

main.o : main.c matr.h
	gcc -g -Wall -Wextra -Wfloat-equal -Werror -std=c99 -pedantic -c main.c 
	
run : a.out
	./a.out
	
a.out : main.o matr.o
	gcc -g -Wall -Wextra -Wfloat-equal -Werror -std=c99 -pedantic main.o matr.o -lm
