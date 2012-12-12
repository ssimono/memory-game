#include <iostream>
#include <sstream>
#include "player.h"
#include "config.h"

using namespace std;

extern Settings settings;

static int playerCount = 0;

Player::Player(Board* board, const char* name)
{
    playerCount++;
    this->score = 0;

    this->name = string(name);

    if(!this->name.size())
    {
	ostringstream oss;
	oss<<"Player #"<<playerCount;
	this->name = oss.str();
    }

    this->setBoard(board);
}

Player::Player(const char* name)
{
    playerCount++;
    this->score = 0;

    this->name = string(name);

    if(!this->name.size())
    {
	ostringstream oss;
	oss<<"Player #"<<playerCount;
	this->name = oss.str();
    }
}

void Player::inscreaseScore()
{
    this->score++;
}

void Player::setBoard(Board* board)
{
    this->board = board;
}

bool Player::play()
{
    if( this->board->isFinished() ) return false;
    
    // First turn:
    int first_value = this->chooseSquare();
    
    // Second turn:
    int second_value = this->chooseSquare( first_value );
    
    // Hide squares:
    this->board->hideVisibleSquares();
    
    return (first_value == second_value);
}

int Player::chooseSquare(int first_value)
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
                try
                {
                    SquarePosition pos = this->board->findSquare(event.button.x, event.button.y);
                    int value = this->board->flipSquareIn(pos.column, pos.line);
                    return value;
                }
                catch(signal::ClickedOutside){ continue; }
                catch(signal::AlreadyFound){ continue; }
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

string Player::getName()
{
    return this->name;
}

//-----------------------------------------------------------------------------

Computer::Computer(Board* board, const char* name):Player(board,name){}
Computer::Computer(const char* name):Player(name){}

void Computer::setBoard(Board* board)
{
    this->board = board;
    this->board->addWatcher(this);
}

void Computer::seeMovement(int x, int y, int value){}

void Computer::seeFoundCouple(int value){}

int Computer::pickRandomSquare()
{
    SDL_Event event;

    while(true)
    {
	// Makes sure user did not ask to quit
	while(SDL_PollEvent(&event))
	    if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN)
		throw signal::UserQuitRequest();

	try
	{
	    int pos = rand()%this->board->getNbSquares();
	    
	    int value = this->board->flipSquareIn(pos);

	    return value;
	}
	catch(signal::AlreadyVisible){ continue; }
        catch(signal::AlreadyFound){ continue; }
    }
}

//-----------------------------------------------------------------------------

DumbComputer::DumbComputer(Board* board):Computer(board){}
DumbComputer::DumbComputer():Computer(){}

int DumbComputer::chooseSquare(int first_value)
{
    SDL_Delay(settings.show_duration/3);
    
    return this->pickRandomSquare();
}

//-----------------------------------------------------------------------------

PerfectComputer::PerfectComputer():Computer(){}

PerfectComputer::PerfectComputer(Board* board):Computer(board){}

void PerfectComputer::setBoard(Board* board)
{
    this->board = board;
    this->board->addWatcher(this);
    
    int N = this->board->getNbSquares()/2;
    this->recolls.reserve( N );
    for(int i=0 ; i<N ; ++i) this->recolls.push_back(new Recollection(i));
}

PerfectComputer::~PerfectComputer()
{
    vector<Recollection*>::iterator it;
    for (it = this->recolls.begin() ; it != this->recolls.end() ; ++it)
        delete *it;
}

int PerfectComputer::chooseSquare(int first_value)
{
    SDL_Delay(settings.show_duration/3);
    
    if( first_value == -1 ) // First turn
    {        
        // First try to find pairs in squares already seen
        vector<Recollection*>::iterator it;
        for (it = this->recolls.begin() ; it != this->recolls.end() ; ++it)
            if( (*it)->getStatus() == MATCHED )
            {
                int pos = (*it)->getPosition1();
                return this->board->flipSquareIn(pos);
            }
        
        // If no pairs has been noticed before, pick random
        return this->pickRandomSquare();
    }
    else // Second turn
    {        
        // First try to flip the sibling of first square flipped
        if( this->recolls[first_value]->getStatus() == MATCHED )
        {
            Recollection* recoll = this->recolls[first_value];
            try{
                return this->board->flipSquareIn( recoll->getPosition2() );
            }catch(signal::AlreadyVisible){
                return this->board->flipSquareIn( recoll->getPosition1() );
            }
        }
        else return this->pickRandomSquare();
    }
}

void PerfectComputer::updateRecolls(int x, int y, int value)
{
    int position = y * this->board->getNbColumns() + x;
    this->recolls[value]->setPosition(position, value);
}

void PerfectComputer::seeMovement(int x, int y, int value)
{
    this->updateRecolls(x,y,value);
}

void PerfectComputer::seeFoundCouple(int value)
{
    this->recolls[value]->clearPosition(value);
}
