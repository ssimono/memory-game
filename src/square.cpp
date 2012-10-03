#include <iostream>
#include <string>
#include <sstream>

#include "game_exception.h"
#include "square.h"

std::string images[23] = {"araignee.bmp","arbre.bmp","ballon.bmp","champignon.bmp","clou.bmp","coquillage.bmp","creme.bmp","douche.bmp","elephant.bmp","fesses.bmp","guitarre.bmp","igloo.bmp","judoka.bmp","maison.bmp","manette.bmp","ours.bmp","pamplemousse.bmp","parapluie.bmp","piece.bmp","poule.bmp","salade.bmp","tasse.bmp","tetine.bmp"};

Square::Square(short id, short value, int position_x, int position_y)
{
    this->id = id;
    this->value = value;
    
    // Loads a SDL_Surface to hold the image data
    // Image is chosen according to square instance's value
    std::string file_path = std::string("share/squares/") + images[this->value];
    this->sdl_surface = SDL_LoadBMP( file_path.c_str() );
    
    // Throw an exception if the file is not correctly loaded
    if(this->sdl_surface == NULL){
        std::ostringstream oss;
        oss<<"Failed to load file "<<file_path<<": "<<SDL_GetError();
        throw GameException(error::CannotLoadFile, oss.str());
    }
    
    SDL_Rect rect;
    rect.x = position_x;
    rect.y = position_y;
    rect.w = SQUARE_WIDTH;
    rect.h = SQUARE_HEIGHT;
    this->rect = rect;
    
    this->status = HIDDEN;
    
    std::clog<<"Square object created ("<<this->id<<')'<<std::endl;
}

Square::~Square()
{
    if(this->sdl_surface != NULL) SDL_FreeSurface(this->sdl_surface);
    std::clog<<"Square object destroyed ("<<this->id<<')'<<std::endl;
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