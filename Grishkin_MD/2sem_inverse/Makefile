all : a.out run



inverse_matrix.o : inverse_matrix.c inverse_matrix.h

	gcc -c -g inverse_matrix.c



main.o : main.c inverse_matrix.h

	gcc -c -g main.c

run : a.out

	./a.out



a.out : main.o inverse_matrix.o

	gcc -g main.o inverse_matrix.o -lm

