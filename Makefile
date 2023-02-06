CC = g++
INCLUDES = includes
SOURCES = sources/*.cpp
BIN = ./main
PROG = main.cpp
FLAGS = -g -Wall -Werror
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full -s

all:
	@$(CC) -o $(BIN) $(PROG) $(SOURCES) -I$(INCLUDES) $(FLAGS)

run: all clear
	@$(BIN)

clear:
	clear

val: all clear
	valgrind $(VFLAGS) $(BIN)

debug: all clear
	gdb $(BIN)