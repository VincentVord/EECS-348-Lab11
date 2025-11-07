# Makefile for Lab11.cpp

# Compiler and flags
CC = g++
CFLAGS = -Wall -Wextra -std=c++11

# Targets (executables)
TARGETS = Lab11

# Default target
all: $(TARGETS)

# Compile Lab11
Lab11: Lab11.cpp
	$(CC) $(CFLAGS) -o Lab11 Lab11.cpp

# Clean up build files
clean:
	rm -f $(TARGETS)

# Run program
run: Lab11
	./Lab11