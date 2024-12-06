EXECUTABLE = avl_tree

CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -O2 # -g - это флаг отладки (убрать в релизе)

OBJECTS = avl_tree.o main.o

$(EXECUTABLE): $(OBJECTS)
	g++ -o $(EXECUTABLE) $(OBJECTS) $(CXXFLAGS)

%.o: %.cpp %.h
	g++ -c $< $(CXXFLAGS)

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

