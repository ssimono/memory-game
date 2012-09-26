#include "board.h"

Board::Board(SDL_Surface* screen, int nb_lines, int nb_columns)
{
    this->screen = screen;
    this->nbLines = nb_lines;
    this->nbColumns = nb_columns;
    
    std::clog<<"Object board created"<<std::endl;
}