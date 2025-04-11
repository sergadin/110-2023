CXX = g++
CXXFLAGS = -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default \
    -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op \
    -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor \
    -Wstrict-null-sentinel  -Wold-style-cast -Woverloaded-virtual \
    -Wsign-promo -Weffc++ -std=c++17

TARGET_SERVER = server
TARGET_CLIENT = client
TARGET_MAIN = main

SRCS_SERVER = server.cpp DataBase.cpp Schedule.cpp Query.cpp SelectingQuery.cpp AssigningQuery.cpp UpdateQuery.cpp InsPrQuery.cpp AuxFun.cpp
SRCS_CLIENT = client.cpp
SRCS_MAIN = Main.cpp DataBase.cpp Schedule.cpp Query.cpp SelectingQuery.cpp AssigningQuery.cpp UpdateQuery.cpp InsPrQuery.cpp AuxFun.cpp

OBJS_SERVER = $(SRCS_SERVER:.cpp=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.cpp=.o)
OBJS_MAIN = $(SRCS_MAIN:.cpp=.o)

INCLUDES = Schedule.h

all: $(TARGET_SERVER) $(TARGET_CLIENT) $(TARGET_MAIN)

$(TARGET_SERVER): $(OBJS_SERVER)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET_CLIENT): $(OBJS_CLIENT)
	$(CXX) $(CXXFLAGS) -o $@ $^
	
$(TARGET_MAIN): $(OBJS_MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^	

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_MAIN) $(TARGET_SERVER) $(TARGET_CLIENT) $(TARGET_MAIN)

.PHONY: all clean
