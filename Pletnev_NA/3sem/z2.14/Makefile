CXXFL = -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default \
    -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op \
    -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor \
    -Wstrict-null-sentinel  -Wold-style-cast -Woverloaded-virtual \
    -Wsign-promo -Weffc++ -std=gnu++11
	
all: run clear

Error.o : Error.cpp Error.h
	g++ $(CXXFL) -c Error.cpp

ParameterContainer.o : ParameterContainer.cpp ParameterContainer.h Error.o
	g++ $(CXXFL) -c ParameterContainer.cpp

main.o : main.cpp ParameterContainer.h
	g++ $(CXXFL) -c main.cpp

a.out: Error.o ParameterContainer.o main.o
	g++ $(CXXFL) Error.o ParameterContainer.o main.o -o a.out -lm

run: a.out
	valgrind --track-origins=yes --leak-check=full -s ./a.out

clear:
	rm Error.o ParameterContainer.o main.o a.out