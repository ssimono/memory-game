#ifndef SQUARE_H
#define SQUARE_H

#include <SDL/SDL.h>

const int SQUARE_WIDTH  = 70;
const int SQUARE_HEIGHT = 70;

enum State{
    VISIBLE,
    HIDDEN,
    DISCOVERED
};

class Square
{
    public:
	Square(short id, short value, int position_x, int position_y);
	~Square();
	
	short getId();
	short getValue();
	
	void show(SDL_Surface* screen);
	void hide(SDL_Surface* screen);
	void reveal(SDL_Surface* screen);
	
    private:
	short id;
	short value;
	State state;
	SDL_Surface* sdl_surface;
	
	SDL_Rect rect;
};

#endif