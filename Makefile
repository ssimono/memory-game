CPP  = g++
CFLAGS = -Wall `sdl-config --cflags`
LIBS = `sdl-config --libs`
COMPILE = $(CPP)

SRC = src/main.cpp src/square.cpp
OBJ = main.o square.o

BIN = memory-game

all:
	$(COMPILE) -c $(SRC)
	$(COMPILE) -o $(BIN) $(OBJ) $(CFLAGS) $(LIBS)

clean:
	rm *.o
	rm $(BIN)
