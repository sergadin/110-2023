CXX = g++
CXXFLAGS = -std=c++20 -Wall

SRCS = main.cpp database.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = workload_db

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp database.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)