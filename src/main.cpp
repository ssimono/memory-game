#include <iostream>
#include <SDL/SDL.h>

SDL_Surface* screen; 

/**
 * Initialize SDL Window and video settings
 *
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

int main(int argc, char** argv)
{
    initSDL();
    
    SDL_Delay(5000);
       
    SDL_FreeSurface(screen);
    
    return EXIT_SUCCESS;
}

