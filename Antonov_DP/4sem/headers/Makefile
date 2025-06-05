all: a.out
	./a.out
List.o: List.cpp Tree.cpp Hash.cpp database.hpp
	g++ -c List.cpp Tree.cpp Hash.cpp
test.o: test.cpp database.hpp student.hpp
	g++ -c test.cpp
a.out: test.o List.o
	g++ test.o List.o Tree.o Hash.o
