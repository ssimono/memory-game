#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "game_exception.h"
#include "square.h"

struct SquarePosition
{
    int column;
    int line;
};

enum Tour
{
    FIRST_TOUR,
    SECOND_TOUR
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
	 * Flip out squares that have been flipped in
	 * should only be called after second tour
	 */
	void hideVisibleSquares();
	
	/**
	 * Return the [column,line] position of the square that has been clicked
	 * by a click event on [x,y]
	 * @return SquarePosition
	 * @throw signal::ClickedOutside if no square is located at the given coordinates
	 */
	SquarePosition findSquare(int x, int y);
	
	/*
	 * Return a boolean telling if all squares have been found
	 */
	bool isFinished();
	
	/**
	 * Return the number of squares on the board
	 */
	int getNbSquares();
	
    private:
	int nbLines;
	int nbColumns;
	
	int nbSquaresFound;
	
	std::vector<Square*> squares;
	SDL_Surface* screen;
	
	Square* visible[2];
	Tour tour;
	
	/**
	 * Fill the board with squares and affect random pairs of values
	 */
	void fill();
	
	/**
	 * Free n first squares, in case nth square crashed
	 * @param n First squares to clean, n not included
	 */
	void cleanFirstSquares(int n);
};

#endif