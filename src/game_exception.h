#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H

#include <string>

namespace error
{
    enum ErrorId
    {
	CannotLoadFile		// Fail to load BMP file with SDL_LoadBMP function
    };
}

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

#endif