#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "square.h"

const int BOARD_ORIGIN_X	= 10;
const int BOARD_ORIGIN_Y	= 10;
const int SQUARE_MARGIN_RIGHT	= 5;
const int SQUARE_MARGIN_BOTTOM	= 5;

struct SquarePosition
{
    int column;
    int line;
};

/**
 * A Board game containing all squares
 * It places squares on the screen, affects random values and handles Square's methods calling
 */
class Board
{
    public:
	Board(SDL_Surface* screen, int nb_lines, int nb_columns);
	~Board();
	
	/**
	 * Flip the square located ad [x,y] on the grid and shows the image
	 * @return Value of the square
	 */
	int flipSquareIn(int x, int y);
	
	/**
	 * Return the [column,line] position of the square that has been clicked
	 * by a click event on [x,y]
	 * @return SquarePosition
	 * @throw int if no square is located at the given coordinates
	 */
	SquarePosition findSquare(int x, int y);
	
    private:
	int nbLines;
	int nbColumns;
	
	std::vector<Square*> squares;
	SDL_Surface* screen;
	
	/**
	 * Fill the board with squares and affect random pairs of values
	 */
	void fill();
};

#endif