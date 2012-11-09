#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

using namespace std;

class Player
{
    public:
	Player(Board* board);
	
	virtual bool play();
	void inscreaseScore();
	
	int getScore();
	string getName();
	
    protected:
	Board* board;
	int score;
	string name;
	
	virtual int chooseSquare();
};

class Computer:public Player
{
    public:
	Computer(Board* board);
};

class DumbComputer:public Computer
{
    public:
	DumbComputer(Board* board);
	bool play();
    
    protected:
	int chooseSquare();
};

#endif
