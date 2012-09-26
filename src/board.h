#ifndef BOARD_H
#define BOARD_H

#include <iostream>

#include "square.h"

const int SQUARE_MARGIN_RIGHT = 5;
const int SQUARE_MARGIN_LEFT  = 5;

class Board
{
    public:
	Board(SDL_Surface* screen, int nb_lines, int nb_columns);
	
	int getWidth();
	int getHeight();
	
    private:
	int nbLines;
	int nbColumns;
	
	SDL_Surface* screen;
};

#endif