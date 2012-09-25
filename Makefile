CPP  = g++
CFLAGS = -Wall `sdl-config --cflags`
LIBS = `sdl-config --libs`
COMPILE = $(CPP)

SRC = src/main.cpp
OBJ = main.o

BIN = memory-game

all:
	$(COMPILE) -c $(SRC)
	$(COMPILE) -o $(BIN) $(OBJ) $(CFLAGS) $(LIBS)

clean:
	rm *.o
	rm $(BIN)
