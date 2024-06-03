all: a.out run

inter.o: inter.c inter.h
	gcc -c inter.c 

main_inter.o: main_inter.c inter.h 
	gcc -c main_inter.c
	
run: a.out
	./a.out
	gnuplot plot1.gnu
	gnuplot plot2.gnu
	gnuplot plot3.gnu
	gnuplot plot4.gnu
	gnuplot plot5.gnu
	gnuplot plot6.gnu
	
a.out: main_inter.o inter.o
	gcc main_inter.o inter.o -lm