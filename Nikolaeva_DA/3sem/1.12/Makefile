CXX = g++
CXXFLAGS = -std=c++11 -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
LDFLAGS = 

all: main

main: main.o triangle.o point.o
	$(CXX) $(LDFLAGS) main.o triangle.o point.o -o main

main.o: main.cpp triangle.h point.h
	$(CXX) $(CXXFLAGS) -c main.cpp

triangle.o: triangle.cpp triangle.h point.h
	$(CXX) $(CXXFLAGS) -c triangle.cpp

point.o: point.cpp point.h
	$(CXX) $(CXXFLAGS) -c point.cpp

clean:
	rm -f *.o main
