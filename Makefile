CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

INCLUDES = -I.

# Source files
APP_SRC = example/main.c

# Targets
APP_TARGET = example/main

.PHONY: all run clean

all: $(APP_TARGET)

$(APP_TARGET): $(APP_SRC) array.h sort.h
	$(CC) $(CFLAGS) $(INCLUDES) -o $(APP_TARGET) $(APP_SRC) $(LIB_SRC)

run: all
	./$(APP_TARGET)

clean:
	rm -f $(APP_TARGET)
