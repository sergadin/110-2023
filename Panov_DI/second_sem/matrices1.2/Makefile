all: a.out run

determ.o: determ.c determ.h
	gcc -c determ.c 

main.o: main.c determ.h 
	gcc -c main.c
	
run: a.out
	./a.out
	gnuplot plot1.gnu
	gnuplot plot2.gnu
	gnuplot plot3.gnu
	
a.out: main.o determ.o
	gcc main.o determ.o -lm
