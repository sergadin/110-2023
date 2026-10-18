CXX = g++

CXXFLAGS = -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format -I./src

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

SRC_FILES = $(SRC_DIR)/triangulate.cpp
OBJ_FILES = $(BUILD_DIR)/triangulate.o

TEST_FILE = $(TEST_DIR)/test.cpp
TEST_EXEC = triangulation.out

all: $(TEST_EXEC)

$(TEST_EXEC): $(OBJ_FILES) $(TEST_FILE)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/triangulate.o: $(SRC_DIR)/triangulate.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TEST_EXEC)

.PHONY: all clean

