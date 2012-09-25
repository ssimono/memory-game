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
	
	short getId();
	short getValue();
	
	void show();
	void hide();
	void reveal();
	
    private:
	short id;
	short value;
	State state;
	
	SDL_Rect rect;
};

#endif