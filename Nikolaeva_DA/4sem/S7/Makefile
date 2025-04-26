CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
LDFLAGS = -pthread

SRV_SRCS = server.cpp StudentDatabase.cpp
CLI_SRCS = client.cpp
APP_SRCS = main.cpp StudentDatabase.cpp

TARGETS = server client student_app

all: $(TARGETS)

server: $(SRV_SRCS)
	$(CXX) $(CXXFLAGS) $(SRV_SRCS) -o $@ $(LDFLAGS)

client: $(CLI_SRCS)
	$(CXX) $(CXXFLAGS) $(CLI_SRCS) -o $@ $(LDFLAGS)

student_app: $(APP_SRCS)
	$(CXX) $(CXXFLAGS) $(APP_SRCS) -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean
run_server:
	./server

run_client:
	./client

run_app:
	./student_app
