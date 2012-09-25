#include "square.h"

Square::Square(short id, short value, int position_x, int position_y)
{
    this->id = id;
    this->value = value;
    
    SDL_Rect rect;
    rect.x = position_x;
    rect.y = position_y;
    rect.w = SQUARE_WIDTH;
    rect.h = SQUARE_HEIGHT;
    this->rect = rect;
    
    this->state = HIDDEN;
}

short Square::getValue()
{
    return this->value;
}

short Square::getId()
{
    return this->id;
}