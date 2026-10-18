CXX = g++
CXXFLAGS = -Wall -g -std=c++11

all: reservation_journal

reservation_journal: main.cpp rest.cpp
	$(CXX) $(CXXFLAGS) -o reservation_journal main.cpp rest.cpp

clean:
	rm -f reservation_journal
