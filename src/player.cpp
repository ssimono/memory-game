#include <iostream>
#include <sstream>
#include "player.h"
#include "config.h"

Player::Player(Board* board)
{
    this->board = board;
    this->score = 0;
    this->name = std::string("Player");
    
    static int playerCount = 0;
    
    std::ostringstream oss;
    oss<<"Player #"<<++playerCount;
    this->name = oss.str();
}

void Player::inscreaseScore()
{
    this->score++;
}

bool Player::play()
{
    if( this->board->isFinished() ) return false;
    
    // First tour:
    int first_value = this->chooseSquare();
    
    // Second tour:
    int second_value = this->chooseSquare();
    
    // Hide squares:
    this->board->hideVisibleSquares();
    
    return (first_value == second_value);
}

int Player::chooseSquare()
{
    SDL_Event event;
    
    // Clean the event queue before waiting event
    while(SDL_PollEvent(&event))
	if(event.type == SDL_QUIT) throw signal::UserQuitRequest();
    
    while(true)
    {
        SDL_WaitEvent(&event);
        
        switch(event.type)
        {
            case SDL_QUIT:
                throw signal::UserQuitRequest();
                break;
	    case SDL_MOUSEMOTION:
		this->board->handleHover(event.motion.x,event.motion.y);
		break;
            case SDL_KEYDOWN:
                throw signal::UserQuitRequest();
                break;
            case SDL_MOUSEBUTTONDOWN:
                using namespace std;
                try
                {
                    SquarePosition pos = this->board->findSquare(event.button.x, event.button.y);
                    int value = this->board->flipSquareIn(pos.column, pos.line);
                    return value;
                }
                catch(signal::ClickedOutside){ continue; }
                catch(signal::AlreadyVisible){ continue; }
            default:
                continue;
        }
    }
}

int Player::getScore()
{
    return this->score;
}

std::string Player::getName()
{
    return this->name;
}

//-----------------------------------------------------------------------------

Computer::Computer(Board* board):Player(board)
{
    int pos = this->name.find('#') - 1;
    this->name.replace(0,pos,"Cpu");
}

//-----------------------------------------------------------------------------

DumbComputer::DumbComputer(Board* board):Computer(board){}

bool DumbComputer::play()
{
    SDL_Delay(500);
    return Computer::play();
}

int DumbComputer::chooseSquare()
{
    while(true)
    {
	try
	{
	    int col = rand()%this->board->getNbColumns();
	    int line = rand()%this->board->getNbLines();
	 
	    int value = this->board->flipSquareIn(col,line);
	    SDL_Delay(600);
	    return value;
	}
	catch(signal::AlreadyVisible){ continue; }
    }
}

