#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

using namespace std;

class Player
{
    public:
	Player(const char* name="");
	Player(Board* board, const char* name="");
	
	bool play();
	void inscreaseScore();
	
	int getScore();
	string getName();

	virtual void setBoard(Board* board);
	
    protected:
	Board* board;
	int score;
	string name;
	
	virtual int chooseSquare();
};

class Computer:public Player
{
    public:
	Computer(const char* name="");
	Computer(Board* board, const char* name="");
        
	void setBoard(Board* board);
	void seeMovement(int x, int y, int value);
};

class DumbComputer:public Computer
{
    public:
	DumbComputer();
	DumbComputer(Board* board);
    
    protected:
	int chooseSquare();
};

#endif
