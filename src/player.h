#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

class Player
{
    public:
	Player(Board* board);
	
	bool play();
	
    private:
	Board* board;
	
	/**
	 * Let the human user choose a square by clicking on it
	 * @return structure containing line and column of chosen square
	 */
	SquarePosition chooseSquare();
};

#endif