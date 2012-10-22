CPP  = g++
CFLAGS = -Wall `sdl-config --cflags`
LIBS = `sdl-config --libs`
COMPILE = $(CPP)

SRC = src/main.cpp src/square.cpp src/board.cpp src/player.cpp src/game.cpp
OBJ = main.o square.o board.o player.o game.o

BIN = memory-game

all:
	$(COMPILE) -c $(SRC)
	$(COMPILE) -o $(BIN) $(OBJ) $(CFLAGS) $(LIBS)

clean:
	rm *.o
	rm $(BIN)
