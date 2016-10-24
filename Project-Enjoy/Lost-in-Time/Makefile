LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CC = g++

CFLAGS = -std=c++11 -g -Wall -Wextra

all: Lost-in-Time

SOURCES = $(wildcard *.cpp) ./state/machine.cpp
OBJECTS = $(wildcard *.o)

.PHONY: clean all

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@


Lost-in-Time: main.o state/machine.o state/statemainmenu.o state/statepause.o
	@echo "** Building the game"
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

clean:
	$(RM) $(OBJECTS)