#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

#include "game_exception.h"
#include "board.h"

Board::Board(SDL_Surface* screen, int nb_lines, int nb_columns)
{
    // Throw an exception id the number of squares is not even
    if(nb_lines&1 && nb_columns&1){
        std::ostringstream oss;
        oss<<"Board need an even number of squares, "<<nb_lines<<"x"<<nb_columns<<" will not work";
        throw GameException(error::SquareNumberOdd, oss.str());
    }
    
    this->screen = screen;
    this->nbLines = nb_lines;
    this->nbColumns = nb_columns;
    this->tour = FIRST_TOUR;
    
    // Allocate required space in memory to make sure vector does not need to reallocate
    // I booked one more spot just in case it does not fit to the very last bit
    this->squares.reserve( (this->getNbSquares() + 1)*sizeof(Square) );
    
    this->fill();
}

Board::~Board()
{
    std::vector<Square*>::iterator it;
    for (it = this->squares.begin() ; it < this->squares.end() ; ++it)
	delete *it;
}

int Board::flipSquareIn(int x, int y)
{
    int id = x + y * this->nbColumns;
    Square* choice = this->squares[id];
    
    choice->flipIn(this->screen);
    
    switch(this->tour)
    {
	case FIRST_TOUR:
	    this->visible[0] = choice;
	    this->tour = SECOND_TOUR;
	    break;
	case SECOND_TOUR:
	    this->visible[1] = choice;
	    SDL_Delay(SHOW_DURATION);
	    break;
	default:
	    break;
    }
    
    return choice->getValue();
}

void Board::hideVisibleSquares()
{
    if(this->tour != SECOND_TOUR)
	throw GameException(error::TurnNotDone,
			    std::string("Cannot flip squares out before second turn"));
    
    Square* first = this->visible[0];
    Square* second = this->visible[1];
    SDL_Surface* s = this->screen;
    
    if(first->getValue() == second->getValue())
    {
	first->markFound(s);
	second->markFound(s);
    }
    else
    {
	first->flipOut(s);
	second->flipOut(s);
    }
    
    this->tour = FIRST_TOUR;
}

SquarePosition Board::findSquare(int x, int y)
{
    // Substract board's origin to get rid of the offset
    x-= BOARD_ORIGIN_X;
    y-= BOARD_ORIGIN_Y;
    
    // Divide x by width of a square: we get column number
    int column = x / (SQUARE_WIDTH+SQUARE_MARGIN_RIGHT);
    if (column >= this->nbColumns ) throw signal::ClickedOutside();
    
    //Divide y by height of a square: we get line number
    int line = y / (SQUARE_HEIGHT+SQUARE_MARGIN_BOTTOM);
    if (line >= this->nbLines ) throw signal::ClickedOutside();
    
    // Make sure player did not click between two squares
    x -= (column+1) * (SQUARE_WIDTH+SQUARE_MARGIN_RIGHT);
    x += SQUARE_MARGIN_RIGHT;
    if (x > 0) throw signal::ClickedOutside();
    
    // Same for click between two vertically aligned squares
    y -= (line+1) * (SQUARE_HEIGHT+SQUARE_MARGIN_BOTTOM);
    y += SQUARE_MARGIN_BOTTOM;
    if (y > 0) throw signal::ClickedOutside();
    
    SquarePosition pos;
    pos.column = column;
    pos.line = line;
    
    return pos;
}

int Board::getNbSquares()
{
    return this->nbLines * this->nbColumns;
}

void Board::fill()
{
    int nb_squares = this->getNbSquares();
    int values[nb_squares];
    
    // Fill values array with couples like {a,a,b,b,c,c...}
    for (int i=0; i < nb_squares/2 ; ++i) values[2*i] = values[2*i+1] = i;
    
    // Shuffle up the values array
    std::random_shuffle(values, values + nb_squares);
    
    for(int i = 0; i < nb_squares; ++i)
    {
	Square* square;
	
	int x = BOARD_ORIGIN_X + (i % this->nbColumns)*(SQUARE_WIDTH+SQUARE_MARGIN_RIGHT),
	    y = BOARD_ORIGIN_Y + (i / this->nbColumns)*(SQUARE_HEIGHT+SQUARE_MARGIN_BOTTOM);
	
	try
	{
	    square = new Square(i, values[i], x, y);
	    square->flipOut(this->screen);
	}
	catch(GameException ge)
	{
	    // If an exception is thrown, we free squares already allocated
	    this->cleanFirstSquares(i);
	    
	    throw ge;
	}
	
	this->squares.push_back(square);
    }
}

void Board::cleanFirstSquares(int n)
{
    for(int i=0; i<n; ++i) delete (this->squares[i]);
}