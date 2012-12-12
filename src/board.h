#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <list>

#include "config.h"
#include "game_exception.h"
#include "square.h"

using namespace std;

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

class Computer;

/**
 * A Board game containing all squares
 * It places squares on the screen, affects random values and handles Square's methods calling
 */
class Board
{
    public:
	Board(SDL_Surface* screen, int nb_lines, int nb_columns);
	Board();
	~Board();
	void init(SDL_Surface* screen, int nb_lines, int nb_columns);
	
	int flipSquareIn(int x, int y);
        int flipSquareIn(int id);
	
	void hideVisibleSquares();
	
	SquarePosition findSquare(int x, int y);
	
	// IMPORTANT please merge this with a findSquare, with a private method used by both!
	void handleHover(int x, int y);
	
	void addWatcher(Computer* computer);

	bool isFinished();
        
	int getNbSquares();
	int getNbLines();
	int getNbColumns();

    private:
	int nbLines;
	int nbColumns;
	
	int nbSquaresFound;
	
	vector<Square*> squares;
	SDL_Surface* screen;
	
	Square* visible[2];
	Square* selected;

	Tour tour;

	list<Computer*> watchers;

	void fill();
	void cleanFirstSquares(int n);
};

#endif
