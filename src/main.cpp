#include <iostream>
#include <time.h>
#include <argp.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "config.h"
#include "game_exception.h"
#include "game.h"
#include "board.h"
#include "player.h"

/**
 * Basic information for command line invocation
 */
const char *argp_program_version = "Memory Game v1.0";
const char *argp_program_bug_address = "<simon@sa-web.fr>";
static char doc[] = "Memory Game - A simple memory game for entertainment";

/**
 * Main SDL_Surface
 */
SDL_Surface* screen;

/**
 * Initialize SDL Window and video settings
 */
void initSDL();


int main(int argc, char** argv)
{
    using namespace std;

    static struct argp argp = { 0, 0, 0, doc };
    argp_parse (&argp, argc, argv, 0, 0, 0);

    cout<<"Starting Memory game"<<endl;
    
    initSDL();
    srand ( time(NULL) );
    
    try
    {
	Board board(screen,NB_LINES, NB_COLUMNS);
	Game game(screen);
	
	for(int i=0; i<nb_players; ++i) game.addPlayer(i%2==0? new Player(&board) : new DumbComputer(&board));
	
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
    
    cout<<"Done"<<endl;

    exit(EXIT_SUCCESS);
}

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

