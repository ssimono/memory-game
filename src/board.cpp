#include "board.h"

Board::Board(SDL_Surface* screen, int nb_lines, int nb_columns)
{
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

int Board::showSquare(int x, int y)
{
    int id = x + y * this->nbColumns;
    Square* choice = this->squares[id];
    
    choice->show(this->screen);
    return choice->getValue();
}

void Board::fill()
{
    int nb_squares = this->nbLines*this->nbColumns;
    
    for(int i = 0; i < nb_squares; ++i)
    {
	int x = BOARD_ORIGIN_X + (i % this->nbLines)*(SQUARE_WIDTH+SQUARE_MARGIN_RIGHT),
	    y = BOARD_ORIGIN_Y + (i / this->nbLines)*(SQUARE_HEIGHT+SQUARE_MARGIN_BOTTOM);
	    
	Square* square = new Square(i, i/2, x, y);
	square->hide(this->screen);
	
	this->squares.push_back(square);
    }
}