all: a.out run

interpolation.o : interpolation.c interpolation.h
gcc - c interpolation.c

main.o : main.c interpolation.h
gcc - c main.c

run : a.out
. / a.out
gnuplot plot1.gnu
gnuplot plot2.gnu
gnuplot plot3.gnu

a.out: main.o interpolation.o
gcc main.o interpolation.o - lm