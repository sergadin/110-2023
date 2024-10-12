all: a.out
	export LD_LIBRARY_PATH=sfml/lib && ./sfml-app
triangle.o: triangle.cpp triangle.h
	g++ -c triangle.cpp
test.o: test.cpp triangle.cpp
	g++ -c test.cpp -Isfml/include
a.out: test.o triangle.o
	g++ test.o -o sfml-app -Lsfml/lib -lsfml-graphics -lsfml-window -lsfml-system triangle.o

