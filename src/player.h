#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

class Player
{
    public:
	Player(Board* board);
	
    private:
	Board* board;
};

#endif