CXX = g++
CXXFL = -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default \
    -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op \
    -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor \
    -Wstrict-null-sentinel  -Wold-style-cast -Woverloaded-virtual \
    -Wsign-promo -Weffc++ -std=gnu++0x

all: run clear

run: a.out
	valgrind --track-origins=yes --leak-check=full -s ./a.out

a.out: main.cpp hashTable.h
	g++ $(CXXFL) -c main.cpp
	g++ main.o -lm

clear:
	rm main.o a.out
