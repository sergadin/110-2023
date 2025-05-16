# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Имя исполняемого файла
TARGET = library

# Список исходных файлов
SOURCES = src/main.cpp \
          src/Library.cpp \
          src/Utils.cpp \
          src/Server.cpp \
          src/Client.cpp

# Список объектных файлов
OBJECTS = $(SOURCES:.cpp=.o)

# Заголовочные файлы
HEADERS = include/Library.h

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Компиляция исходных файлов в объектные
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
