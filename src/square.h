#ifndef SQUARE_H
#define SQUARE_H

#include <SDL/SDL.h>

#include "game_exception.h"

/**
 * Differents status a square can have
 */
enum Status
{
    VISIBLE,
    HIDDEN,
    FOUND
};

/**
 * A square on the board game
 * This contains a value (image) and is located at a specific location
 */
class Square
{
    public:
	Square(short id, short value, int position_x, int position_y);
	~Square();
	
	short getId();
	short getValue();
	
	void flipIn(SDL_Surface* screen);
	void flipOut(SDL_Surface* screen);
	void markFound(SDL_Surface* screen);
	void highlight(SDL_Surface* screen);
	void unHighlight(SDL_Surface* screen);

    private:
	short id;
	short value;
	Status status;
	SDL_Surface* sdl_surface;
	
	SDL_Rect rect;
};

#endif
