#include "square.h"

#include <iostream>
#include <string>

std::string images[5] = {"clou.bmp","colquillage.bmp","creme.bmp","douche.bmp","elephant.bmp"};

Square::Square(short id, short value, int position_x, int position_y)
{
    this->id = id;
    this->value = value;
    this->sdl_surface = SDL_LoadBMP( ( std::string("share/squares/") + images[this->value] ).c_str() );
    std::clog<<SDL_GetError()<<std::endl;
    
    SDL_Rect rect;
    rect.x = position_x;
    rect.y = position_y;
    rect.w = SQUARE_WIDTH;
    rect.h = SQUARE_HEIGHT;
    this->rect = rect;
    
    this->state = HIDDEN;
    
    std::clog<<"Object square created"<<std::endl;
}

Square::~Square()
{
    int i = 3;
    SDL_FreeSurface(this->sdl_surface);
    std::clog<<"Object square destroyed"<<std::endl;
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
    SDL_BlitSurface(this->sdl_surface, NULL, screen, &this->rect);
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