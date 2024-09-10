all: a.out run

interpolationOfFunc.o: interpolationOfFunc.c interpolationOfFunc.h
	gcc -c interpolationOfFunc.c 

main.o: main.c interpolationOfFunc.h 
	gcc -c main.c
	
run: a.out
	./a.out
	gnuplot plot1.gnu
	gnuplot plot2.gnu
	gnuplot plot3.gnu
	
a.out: main.o interpolationOfFunc.o
	gcc main.o interpolationOfFunc.o -lm
