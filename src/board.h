#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

#include "square.h"

const int BOARD_ORIGIN_X	= 10;
const int BOARD_ORIGIN_Y	= 10;
const int SQUARE_MARGIN_RIGHT	= 5;
const int SQUARE_MARGIN_BOTTOM	= 5;

class Board
{
    public:
	Board(SDL_Surface* screen, int nb_lines, int nb_columns);
	
	int getWidth();
	int getHeight();
	
    private:
	int nbLines;
	int nbColumns;
	
	std::vector<Square> squares;
	SDL_Surface* screen;
	
	void fill();
};

#endif