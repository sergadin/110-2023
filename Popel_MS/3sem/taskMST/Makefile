CXXFL = -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default \
    -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op \
    -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor \
    -Wstrict-null-sentinel  -Wold-style-cast -Woverloaded-virtual \
    -Wsign-promo -Weffc++ -std=gnu++0x

all: run clear

run: a.out
	valgrind --track-origins=yes --leak-check=full -s ./a.out

a.out: geom_obj.o mst.o main.o
	g++ $(CXXFL) -c geom_obj.cpp
	g++ $(CXXFL) -c mst.cpp
	g++ $(CXXFL) -c main.cpp
	g++ geom_obj.o mst.o main.o -lm

clear:
	rm geom_obj.o mst.o main.o a.out

