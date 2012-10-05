#include <iostream>
#include <time.h>
#include <SDL/SDL.h>

#include "game_exception.h"
#include "board.h"
#include "player.h"

// Main SDL_Surface
SDL_Surface* screen;

// Board dimensions
const int nb_lines = 5;
const int nb_columns = 4;

/**
 * Initialize SDL Window and video settings
 */
void initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr<<"Error at initializing SDL"<<SDL_GetError()<<'\n';
        exit(EXIT_FAILURE);
    }
    atexit(SDL_Quit);
    
    int width = BOARD_ORIGIN_X + nb_columns * (SQUARE_WIDTH + SQUARE_MARGIN_RIGHT);
    int height = BOARD_ORIGIN_Y + nb_lines * (SQUARE_HEIGHT + SQUARE_MARGIN_BOTTOM);
    
    screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
    if (screen == NULL) {
        std::cerr<<"Cannot initialize graphic mode"<<SDL_GetError()<<'\n';
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Memory game", NULL);
    
    SDL_FillRect(screen, NULL, 0xdfdfdf);
    SDL_UpdateRect(screen, 0,0,width,height);
}

int main(int argc, char** argv)
{
    using namespace std;
    
    initSDL();
    srand ( time(NULL) );
    
    try
    {
	Board board(screen,nb_lines,nb_columns);
    
	Player chuck(&board);
	
	do
	{
	    while(chuck.play()) chuck.getPoint();
	}while( !board.isFinished() );
    }
    catch(signal::UserQuitRequest) {}
    catch(GameException ge)
    {
	SDL_FreeSurface(screen);
	
	cerr<<"[Error] "<<ge.getMessage()<<endl;
	cerr<<"Terminating"<<endl;
	
	return EXIT_FAILURE;
    }
    
    SDL_FreeSurface(screen);
    
    return EXIT_SUCCESS;
}

