all: a.out run clear

point.o: point.cpp point.h
	g++ -c point.cpp

line.o: line.cpp line.h
	g++ -c line.cpp

polygon.o: polygon.cpp polygon.h
	g++ -c polygon.cpp

main.o: main.cpp point.h line.h polygon.h
	g++ -c main.cpp

run: a.out
	./a.out

a.out: point.o line.o polygon.o main.o
	g++ -o point.o line.o polygon.o main.o -lm

clear:
	rm -f *.o main
