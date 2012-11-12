#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

using namespace std;

class Player
{
    public:
	Player(Board* board, const char* name="");
	
	bool play();
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
	Computer(Board* board, const char* name="");
};

class DumbComputer:public Computer
{
    public:
	DumbComputer(Board* board);
    
    protected:
	int chooseSquare();
};

#endif
