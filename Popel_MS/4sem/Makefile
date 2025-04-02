CXX = g++
CXXFLAGS = -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default \
    -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op \
    -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor \
    -Wstrict-null-sentinel  -Wold-style-cast -Woverloaded-virtual \
    -Wsign-promo -Weffc++ -std=c++17

TARGET = a.out

SRCS = Main.cpp Schedule.cpp Query.cpp SelectingQuery.cpp AssigningQuery.cpp UpdateQuery.cpp InsPrQuery.cpp AuxFun.cpp DataBase.cpp

OBJS = $(SRCS:.cpp=.o)

INCLUDES = Schedule.h

all: run clear

run: $(TARGET)
	valgrind --track-origins=yes --leak-check=full -s ./$(TARGET)
	$(MAKE) clear

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -g -o $@ $^

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clear:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clear run

