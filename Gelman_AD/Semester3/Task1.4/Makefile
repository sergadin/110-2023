all: a.out run

polygon_distance.o: polygon_distance.cpp polygon_distance.h
	gcc -c polygon_distance.cpp

main.o: main.cpp interpolation.h
	gcc -c main.cpp

run: a.out
	./a.out

	gnuplot plot1.gnu
	gnuplot plot2.gnu
	gnuplot plot3.gnu

a.out: main.o polygon_distance.o
	gcc main.o polygon_distance.o - lm