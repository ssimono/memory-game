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

void Square::show(SDL_Surface* screen)
{
    SDL_FillRect(screen, &this->rect, 0xff00ff);
    SDL_UpdateRect(screen, this->rect.x,this->rect.y,this->rect.w,this->rect.h);
}

void Square::hide(SDL_Surface* screen)
{
    SDL_FillRect(screen, &this->rect, 0x00ff00);
    SDL_UpdateRect(screen, this->rect.x,this->rect.y,this->rect.w,this->rect.h);
}

void Square::reveal(SDL_Surface* screen)
{
    SDL_FillRect(screen, &this->rect, 0xff0000);
    SDL_UpdateRect(screen, this->rect.x,this->rect.y,this->rect.w,this->rect.h);
}