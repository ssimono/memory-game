#include <iostream>
#include <time.h>
#include <argp.h>
#include <regex.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "config.h"
#include "game_exception.h"
#include "game.h"
#include "board.h"
#include "player.h"

using namespace std;

/**
 * settings set at runtime
 */
Settings settings;

/**
 * Basic information for command line invocation
 */
const char* argp_program_version = "Memory Game v1.0";
const char* argp_program_bug_address = "<simon@sa-web.fr>";
static char doc[] =
"Memory Game - A simple memory game for entertainment\v\
DESCRIPTION\n\
\t--players, -p:\n\
\t\tValue of this option is a string matching (H|C){1,6}\n\
\t\tH adds a human player\n\
\t\tC adds a computer A.I\n\
\t\te.g. -p HCHC will launch a four players game with two humans and 2 A.I";

/**
 * Command line options definition
 */
static struct argp_option options[] =
{
    {	// String used to define type and number of players
	"players",'p',
	"PLAYERS_LIST",
	0,
	"Specify type and number of players, default to \"HC\""
    },
    {	// Integer representing milliseconds if showing time
	"show-duration",'s',
	"SHOW_DURATION",
	0,
	"Specify time in milliseconds during which cards are shown"
    },
    { 0 }
};

/**
 * Command line options parser
 * Will be called directly by argp
 */
static error_t parse_opt (int key, char *arg, struct argp_state *state);

/**
 * Main SDL_Surface
 */
SDL_Surface* screen;

/**
 * Initialize SDL Window and video settings
 */
void initSDL();

//-----------------------------------------------------------------------------
//  MAIN FUNCTION
//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
    // Set default settings values
    settings.players_list = string("HC");
    settings.show_duration = 1500;
    
    // Parse arguments and set new settings values if needed
    static struct argp argp = { options, parse_opt, 0, doc };
    argp_parse (&argp, argc, argv, 0, 0, 0);
    
    cout<<"Starting Memory game"<<endl;
    
    // Initialize window and video settings
    initSDL();

    // Initialize random number generator
    srand ( time(NULL) );
    
    try
    {
	// Declare Board and Game objects
	Board board(screen,NB_LINES, NB_COLUMNS);
	Game game(screen);
	
	// Generate players according to players_list string
	int T = settings.players_list.size();
	for(int i=0; i<T; ++i) switch(settings.players_list[i])
	{
	    case 'H':
		game.addPlayer(new Player(&board));
		break;
	    case 'C':
		game.addPlayer(new DumbComputer(&board));
		break;
	    default:break;
	}
	
	// Start the game
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
   
    // Free screen allocated memory
    SDL_FreeSurface(screen);
    
    cout<<"Done"<<endl;

    exit(EXIT_SUCCESS);
}
//-----------------------------------------------------------------------------
//  END OF MAIN
//-----------------------------------------------------------------------------

void initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr<<"Error at initializing SDL"<<SDL_GetError()<<'\n';
        exit(EXIT_FAILURE);
    }
    atexit(SDL_Quit);
    
    int width = get_screen_width();
    int height = get_screen_height(settings.players_list.size());
    
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

static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
    switch (key)
    {
	case 'p': // Players list
	{
	    // Validation regular expression
	    const char* str_regex = "^(H|C){1,6}$";
	    
	    // Regular expression structure
	    regex_t preg;
	    
	    // Compilation
	    regcomp (&preg, str_regex, REG_NOSUB|REG_EXTENDED);

	    // Test
	    if( regexec(&preg, arg, 0, NULL, 0) == REG_NOMATCH )
	    {
		cerr<<"Warning: \""<<arg<<"\" is not a valid players list string."<<endl;
		cerr<<"Default value \"HC\" has been used instead"<<endl;
	    }
	    else settings.players_list = string(arg);

	    // Free preg struture
	    regfree (&preg);

	    break;
	}
	case 's': // Showing time
	{
	    // Validation regular expression
	    const char* str_regex = "^[[:digit:]]{1,4}$";
	    
	    // Regular expression structure
	    regex_t preg;
	    
	    // Compilation
	    regcomp (&preg, str_regex, REG_NOSUB|REG_EXTENDED);

	    // Test
	    if( regexec(&preg, arg, 0, NULL, 0) == REG_NOMATCH )
	    {
		cerr<<"Warning: \""<<arg<<"\" is not a valid showing time number"<<endl;
		cerr<<"Must be an integer between 1 and 9999 milliseconds"<<endl;
		cerr<<"Default value 1500 has been used instead"<<endl;
	    }
	    else settings.show_duration = atoi(arg);

	    // Free preg struture
	    regfree (&preg);

	    break;
	}
	case ARGP_KEY_ARG:
	    // Too many arguments, redirect to usage
	    if (state->arg_num >= 1) argp_usage (state);
	    break;
	
	default:
	    return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
