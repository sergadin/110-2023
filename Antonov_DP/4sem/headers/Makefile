all: a.out
	./a.out
Hash.o: Tree.cpp Tree.hpp
	g++ -c Tree.cpp
test.o: test.cpp database.hpp student.hpp
	g++ -c test.cpp
a.out: test.o Tree.o
	g++ test.o Tree.o
