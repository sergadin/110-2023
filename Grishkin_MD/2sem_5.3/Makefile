all : a.out run



interpolation.o : interpolation.c interpolation.h

	gcc -c -g interpolation.c



main.o : main.c interpolation.h

	gcc -c -g main.c

run : a.out

	./a.out

        gnuplot plot1.gnu



a.out : main.o interpolation.o

	gcc -g main.o interpolation.o -lm
