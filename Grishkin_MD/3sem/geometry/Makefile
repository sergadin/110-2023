CXX=g++
CXXFLAGS=-Wall -g

convexhull: main.o ConvexHull.o Point.o
	$(CXX) $(CXXFLAGS) -o ConvexHull main.o ConvexHull.o Point.o

main.o: main.cpp ConvexHull.h Point.h
	$(CXX) $(CXXFLAGS) -c main.cpp

ConvexHull.o: ConvexHull.cpp ConvexHull.h Point.h
	$(CXX) $(CXXFLAGS) -c ConvexHull.cpp

Point.o: Point.cpp Point.h
	$(CXX) $(CXXFLAGS) -c Point.cpp

clean:
	rm -f *.o a.out

