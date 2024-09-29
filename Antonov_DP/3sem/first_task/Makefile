all: a.out
      ./a.out

%.o: %.cpp
      g++ -c -g $< -o $@

intset.o: intset.cpp intset.h
test.o: test.cpp intset.h

a.out: intset.o test.o
      g++ -o test intset.o test.o
