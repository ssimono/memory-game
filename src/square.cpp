#include <iostream>
#include <string>

#include "square.h"

std::string images[8] = {"clou.bmp","coquillage.bmp","creme.bmp","douche.bmp","elephant.bmp","fesses.bmp","guitarre.bmp","igloo.bmp"};

Square::Square(short id, short value, int position_x, int position_y)
{
    this->id = id;
    this->value = value;
    
    // Loads a SDL_Surface to hold the image data
    this->sdl_surface = SDL_LoadBMP( ( std::string("share/squares/") + images[this->value] ).c_str() );
    
    SDL_Rect rect;
    rect.x = position_x;
    rect.y = position_y;
    rect.w = SQUARE_WIDTH;
    rect.h = SQUARE_HEIGHT;
    this->rect = rect;
    
    this->status = HIDDEN;
    
    std::clog<<"Object square created ("<<this->id<<')'<<std::endl;
}

Square::~Square()
{
    int i = 3;
    SDL_FreeSurface(this->sdl_surface);
    std::clog<<"Object square destroyed ("<<this->id<<')'<<std::endl;
}

short Square::getValue()
{
    return this->value;
}

short Square::getId()
{
    return this->id;
}

void Square::flipIn(SDL_Surface* screen)
{
    this->status = VISIBLE;
    SDL_BlitSurface(this->sdl_surface, NULL, screen, &this->rect);
    SDL_UpdateRect(screen, this->rect.x,this->rect.y,this->rect.w,this->rect.h);
}

void Square::flipOut(SDL_Surface* screen)
{
    this->status = HIDDEN;
    SDL_FillRect(screen, &this->rect, 0x00ff00);
    SDL_UpdateRect(screen, this->rect.x,this->rect.y,this->rect.w,this->rect.h);
}

void Square::markFound(SDL_Surface* screen)
{
    this->status = FOUND;
    SDL_FillRect(screen, &this->rect, 0xff0000);
    SDL_UpdateRect(screen, this->rect.x,this->rect.y,this->rect.w,this->rect.h);
}