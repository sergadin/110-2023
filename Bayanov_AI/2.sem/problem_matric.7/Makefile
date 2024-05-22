TARGET = ./main.out
HDRS_DIR = \
		utils
SRCS = \
        main.c \
		speedy_descent.c
.PHONY: all, build, clean, run

$(TARGET): 
		gcc -I $(HDRS_DIR) $(SRCS) -o $(TARGET) -lm

all: clean build

build: $(TARGET)

clean:
		rm -rf $(TARGET)
run:
		$(TARGET) 