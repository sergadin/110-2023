TARGET = ./main.out
HDRS_DIR = \
		utils
SRCS = \
        all.cpp \
		polygon.cpp
.PHONY: all, build, clean, run

$(TARGET): 
		g++ -I $(HDRS_DIR) $(SRCS) -o $(TARGET)

all: clean build

build: $(TARGET)

clean:
		rm -rf $(TARGET)
run:
		$(TARGET) 