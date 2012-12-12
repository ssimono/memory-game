#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "recollection.h"

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
	
	virtual int chooseSquare(int first_value = -1);
};

class Computer:public Player
{
    public:
	Computer(const char* name="");
	Computer(Board* board, const char* name="");
        
	void setBoard(Board* board);
	virtual void seeMovement(int x, int y, int value);
        virtual void seeFoundCouple(int value);
    
    protected:
        int pickRandomSquare();
};

class DumbComputer:public Computer
{
    public:
	DumbComputer();
	DumbComputer(Board* board);
    
    protected:
	int chooseSquare(int first_value = -1);
};

class PerfectComputer:public Computer
{
    public:
        PerfectComputer();
        PerfectComputer(Board* board);
        ~PerfectComputer();

        void setBoard(Board* board);
        void seeMovement(int x, int y, int value);
        void seeFoundCouple(int value);

    protected:
        vector<Recollection*> recolls;

        int chooseSquare(int first_value = -1);
        void updateRecolls(int x, int y, int value);
};

#endif
