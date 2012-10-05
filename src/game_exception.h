#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H

#include <SDL/SDL.h>

#include <string>
#include <sstream>

/**
 * Class used to handle exception through program process
 */
class GameException
{
    public:
	GameException()
	{
	    this->message = std::string("A game exception has occured");
	}
	GameException(std::string message)
	{
	    this->message = message;
	}
	
	GameException(char* message)
	{
	    this->message = std::string(message);
	}
	
	std::string getMessage() { return this->message;}
	
    protected:
	std::string message;
};

/**
 * Unlike GameException, GameSignal instances are meant to be thrown as part
 * of the game workflow, they do not terminate the game
 */
class GameSignal:public GameException{};

// Definition of throwable errors and signals:

namespace error
{
    class SquareNumberOdd:public GameException
    {
	public: SquareNumberOdd(int nb_lines, int nb_columns){
	    std::ostringstream oss;
	    oss<<"Board need an even number of squares, "<<nb_lines<<"x"<<nb_columns<<" will not work";
	    this->message = oss.str();
	}
    };
    
    class CannotLoadFile:public GameException
    {
	public: CannotLoadFile(std::string path){
	    std::ostringstream oss;
	    oss<<"Failed to load file "<<path<<": "<<SDL_GetError();
	    this->message = oss.str();
	}
    };
    
    class TurnNotDone:public GameException
    {
	public: TurnNotDone():GameException(std::string("Cannot flip squares out before second turn")){};
    };
}

namespace signal
{
    class ClickedOutside:public GameSignal{};
    class UserQuitRequest:public GameSignal{};
    class AlreadyVisible:public GameSignal{};
}

#endif