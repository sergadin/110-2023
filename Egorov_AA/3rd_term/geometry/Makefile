CXX = g++

SRC = main.cpp line.cpp point.cpp polygon.cpp
OBJ = $(SRC:.cpp=.o)
DEPS = line.h point.h polygon.h
TARGET = prog

all: $(TARGET)

$(TARGET): $(OBJ)
	g++ -o $@ $^

%.o: %.cpp $(DEPS)
	g++ -c $< -o $@
	
clear:
	rm -f $(OBJ) $(TARGET)
