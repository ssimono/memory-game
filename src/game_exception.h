#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H

#include <string>

namespace error
{
    enum ErrorId
    {
	UnknownError,
	CannotLoadFile,		// Fail to load BMP file with SDL_LoadBMP function
	SquareNumberOdd		// Odd number of squares on the board
    };
}

/**
 * Class used to handle exception through program process
 */
class GameException
{
    public:
	GameException(error::ErrorId id, std::string message)
	{
	    this->id = id;
	    this->message = message;
	}
	
	GameException(error::ErrorId id, char* message)
	{
	    this->id = id;
	    this->message = std::string(message);
	}
	
	std::string getMessage() { return this->message;}
	error::ErrorId getId() { return this->id;}
	
    private:
	error::ErrorId id;
	std::string message;
};

/**
 * Unlike GameException, GameSignal instances are meant to be thrown as part
 * of the game workflow, they do not terminate the game
 */
class GameSignal:public GameException
{
    public:
	GameSignal() : GameException(error::UnknownError,std::string("")) {}
};

#endif