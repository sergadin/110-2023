CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
LDFLAGS = -pthread

all: program docs

program: main server client

main: main.o StudentDatabase.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

server: server.o StudentDatabase.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

client: client.o StudentDatabase.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

docs: documentation.pdf

documentation.pdf: documentation.tex
	xelatex -interaction=nonstopmode documentation.tex
	xelatex -interaction=nonstopmode documentation.tex
	rm -f *.aux *.log *.out *.toc

clean:
	rm -f *.o main server client documentation.pdf
