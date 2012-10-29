#include <iostream>
#include <vector>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "config.h"
#include "game_exception.h"
#include "game.h"
#include "board.h"
#include "player.h"

// Main SDL_Surface
SDL_Surface* screen;

// Number of players
const int nb_players = 3;

//Return screen dimensions according to graphical constants (see config.c)
int get_screen_height();
int get_screen_width();

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
    
    int width = get_screen_width();
    int height = get_screen_height();
    
    screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
    if (screen == NULL) {
        std::cerr<<"Cannot initialize graphic mode"<<SDL_GetError()<<'\n';
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Memory game", NULL);
    
    if(TTF_Init() < 0) {
	std::cerr<<"Cannot initialize SDL_TTF"<<TTF_GetError()<<endl;
	exit(EXIT_FAILURE);
    }
    atexit(TTF_Quit);
	
    SDL_FillRect(screen, NULL, BACKGROUND_COLOR);
    SDL_UpdateRect(screen, 0,0,width,height);
}

int main(int argc, char** argv)
{
    using namespace std;
    
    cout<<"Starting Memory game"<<endl;
    
    initSDL();
    srand ( time(NULL) );
    
    try
    {
	Board board(screen,NB_LINES, NB_COLUMNS);
	Game game(screen);
	
	for(int i=0; i<nb_players; ++i) game.addPlayer(i%2==0? new Player(&board) : new Computer(&board));
	
	game.start();
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
    
    cout<<"\nDone"<<endl;

    exit(EXIT_SUCCESS);
}

int get_screen_height()
{
    return max(BOARD_ORIGIN_Y + NB_LINES * (SQUARE_HEIGHT + SQUARE_MARGIN_BOTTOM),
	       nb_players * SCORE_PANEL_HEIGHT);
}

int get_screen_width()
{
    return	BOARD_ORIGIN_X +
		NB_COLUMNS * (SQUARE_WIDTH + SQUARE_MARGIN_RIGHT) +
		SCORE_PANEL_WIDTH;
}

