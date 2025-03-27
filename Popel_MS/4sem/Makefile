CXX = g++


CXXFLAGS = -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default \
    -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op \
    -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor \
    -Wstrict-null-sentinel  -Wold-style-cast -Woverloaded-virtual \
    -Wsign-promo -Weffc++ -std=c++17


TARGET = prog


SRCS = Main.cpp Schedule.cpp Query.cpp SelectingQuery.cpp AssigningQuery.cpp UpdateQuery.cpp InsPrQuery.cpp AuxFun.cpp DataBase.cpp


OBJS = $(SRCS:.cpp=.o)


INCLUDES = Schedule.h

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
.PHONY: all clean run
