CPP  = g++
CFLAGS = -Wall `sdl-config --cflags` -lSDL_ttf
LIBS = `sdl-config --libs`
COMPILE = $(CPP)

SRC = src/main.cpp src/square.cpp src/board.cpp src/player.cpp src/game.cpp src/recollection.cpp
OBJ = main.o square.o board.o player.o game.o recollection.o

BIN = memory-game

all:
	$(COMPILE) -c $(SRC)
	$(COMPILE) -o $(BIN) $(OBJ) $(CFLAGS) $(LIBS)

release:
	$(COMPILE) -DRELEASE -c $(SRC)
	$(COMPILE) -o $(BIN) $(OBJ) $(CFLAGS) $(LIBS)
clean:
	rm *.o
	rm $(BIN)
