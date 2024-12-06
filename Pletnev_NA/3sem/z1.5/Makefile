CXXFL = -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default \
    -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op \
    -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor \
    -Wstrict-null-sentinel  -Wold-style-cast -Woverloaded-virtual \
    -Wsign-promo -Weffc++ -std=gnu++11
	
all: run clear

Error.o : Error.cpp Error.h
	g++ $(CXXFL) -c Error.cpp

Point.o : Point.cpp Point.h Error.o
	g++ $(CXXFL) -c Point.cpp

Polygon.o : Polygon.cpp Polygon.h Point.o
	g++ $(CXXFL) -c Polygon.cpp

main.o : main.cpp Polygon.h
	g++ $(CXXFL) -c main.cpp

a.out: Error.o Point.o Polygon.o main.o
	g++ $(CXXFL) Error.o Point.o Polygon.o main.o -o a.out -lm

run: a.out
	valgrind --track-origins=yes --leak-check=full -s ./a.out

clear:
	rm Error.o Point.o Polygon.o main.o a.out