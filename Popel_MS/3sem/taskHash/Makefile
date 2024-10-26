CXX = g++
CXXFL = -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default \
    -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op \
    -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor \
    -Wstrict-null-sentinel  -Wold-style-cast -Woverloaded-virtual \
    -Wsign-promo -Weffc++ -std=gnu++0x

all: run clear

run: a.out
	valgrind --track-origins=yes --leak-check=full -s ./a.out

a.out: hashTable.o main.o
	g++ $(CXXFL) -c hashTable.cpp
	g++ $(CXXFL) -c main.cpp
	g++ hashTable.o main.o -lm

clear:
	rm hashTable.o main.o a.out

