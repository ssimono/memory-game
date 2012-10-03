#include <iostream>
#include <time.h>
#include <SDL/SDL.h>

#include "game_exception.h"
#include "board.h"
#include "player.h"

// Main SDL_Surface
SDL_Surface* screen;

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
    
    screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    if (screen == NULL) {
        std::cerr<<"Cannot initialize graphic mode"<<SDL_GetError()<<'\n';
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Memory game", NULL);
}

/**
 * Function used for debug purpose
 */
void waitForKey()
{
    SDL_Event event;
    
    do
    {
        SDL_WaitEvent(&event);
    }while(event.type != SDL_QUIT && event.type != SDL_KEYDOWN);
}

int main(int argc, char** argv)
{
    using namespace std;
    
    initSDL();
    srand ( time(NULL) );
    
    try
    {
	Board board(screen,5,6);
    
	Player chuck(&board);
    
	while(chuck.play());
    }
    catch(GameException ge)
    {
	SDL_FreeSurface(screen);
	
	cerr<<"[code #"<<ge.getId()<<"] "<<ge.getMessage()<<endl;
	cerr<<"Terminating"<<endl;
	
	return EXIT_FAILURE;
    }
    
    waitForKey();
    SDL_FreeSurface(screen);
    
    return EXIT_SUCCESS;
}

