#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H

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

#endif