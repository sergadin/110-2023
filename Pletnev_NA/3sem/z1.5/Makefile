all : a.out run

Vector.o : Vector.h Vector.cpp
	gcc -c Vector.cpp

Dot.o : Dot.h Dot.cpp
	gcc -c Dot.cpp

Polygon.o : Polygon.h Polygon.cpp Dot.o
	gcc -c Polygon.cpp


main.o : main.cpp Vector.o Dot.o Polygon.o
	gcc -c main.cpp
	
run : a.out
	./a.out
	
a.out : main.o Vector.o Dot.o Polygon.o
	gcc main.o Vector.o Dot.o Polygon.o -lm
