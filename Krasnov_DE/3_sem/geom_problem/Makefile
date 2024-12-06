CXX = g++

CXXFLAGS = -Wall -g -I/path/to/gnuplot-iostream -I/path/to/boost

SRCS = main.cpp polygon1.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = my_program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ -lboost_iostreams -lboost_system -lboost_filesystem

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
