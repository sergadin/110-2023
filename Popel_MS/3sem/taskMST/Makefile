all: run clear

run: a.out
	valgrind --track-origins=yes --leak-check=full -s ./a.out

a.out: geom_obj.o mst.o main.o
	g++ -c geom_obj.cpp
	g++ -c mst.cpp
	g++ -c main.cpp
	g++ geom_obj.o mst.o main.o -lm

clear:
	rm geom_obj.o mst.o main.o a.out

