#include <algorithm>

#include "board.h"

Board::Board(SDL_Surface* screen, int nb_lines, int nb_columns)
{
    if(nb_lines&1 && nb_columns&1) throw 'e';
    
    this->screen = screen;
    this->nbLines = nb_lines;
    this->nbColumns = nb_columns;
    
    this->squares.reserve( (nb_lines*nb_columns + 1)*sizeof(Square) );
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
    return choice->getValue();
}

void Board::fill()
{
    int nb_squares = this->nbLines*this->nbColumns;
    
    int values[nb_squares];
    for (int i=0; i < nb_squares/2 ; ++i) values[2*i] = values[2*i+1] = i;
    
    std::random_shuffle(values, values + nb_squares);
    
    for(int i = 0; i < nb_squares; ++i)
    {
	int x = BOARD_ORIGIN_X + (i % this->nbColumns)*(SQUARE_WIDTH+SQUARE_MARGIN_RIGHT),
	    y = BOARD_ORIGIN_Y + (i / this->nbColumns)*(SQUARE_HEIGHT+SQUARE_MARGIN_BOTTOM);
	    
	Square* square = new Square(i, values[i], x, y);
	square->flipOut(this->screen);
	
	this->squares.push_back(square);
    }
}