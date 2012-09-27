#ifndef SQUARE_H
#define SQUARE_H

#include <SDL/SDL.h>

const int SQUARE_WIDTH  = 70;
const int SQUARE_HEIGHT = 70;

enum State
{
    VISIBLE,
    HIDDEN,
    FOUND
};

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
	
    private:
	short id;
	short value;
	State state;
	SDL_Surface* sdl_surface;
	
	SDL_Rect rect;
};

#endif