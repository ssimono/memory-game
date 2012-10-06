#include <iostream>
#include <vector>
#include <time.h>
#include <SDL/SDL.h>

#include "game_exception.h"
#include "board.h"
#include "player.h"
#include "thread.h"

// Main SDL_Surface
SDL_Surface* screen;

// Board dimensions
const int nb_lines = 5;
const int nb_columns = 4;

// Number of players
const int nb_players = 2;

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
    
    CountTo10 my_thread = CountTo10();
    my_thread.start();
    
    try
    {
	Board board(screen,nb_lines,nb_columns);
	vector<Player*> players;
	
	for(int i=0; i<nb_players; ++i) players.push_back(new Player(&board));
	
	std::vector<Player*>::iterator it = players.begin();
	Player* current_player;
	
	do
	{
	    current_player = (*it);
	    while(current_player->play()) current_player->inscreaseScore();
	    
	    ++it;
	    if( it == players.end() ) it = players.begin();
	    
	    cout<<"Change player"<<endl;
	    
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
    
    my_thread.stop();
    
    SDL_FreeSurface(screen);

    return EXIT_SUCCESS;
}

