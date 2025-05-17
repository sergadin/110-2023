all: a.out
	./a.out
Hash.o: Hash.cpp Hash.hpp
	g++ -c Hash.cpp
test.o: test.cpp database.hpp student.hpp
	g++ -c test.cpp
a.out: test.o Hash.o
	g++ test.o Hash.o
