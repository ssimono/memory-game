#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

class Player
{
    public:
	Player(Board* board);
	
	bool play();
	
	void inscreaseScore();
	
    private:
	Board* board;
	int score;
	/**
	 * Let the human user choose a square by clicking on it
	 * @return value of the chosen square
	 */
	int chooseSquare();
};

namespace signal
{
    class UserQuitRequest:public GameSignal{};
}
#endif