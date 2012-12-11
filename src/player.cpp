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
//-----------------------------------------------------------------------------

DumbComputer::DumbComputer(Board* board):Computer(board){}
DumbComputer::DumbComputer():Computer(){}

int DumbComputer::chooseSquare()
{
    SDL_Delay(settings.show_duration/3);

    SDL_Event event;

    while(true)
    {
	// Makes sure user did not ask to quit
	while(SDL_PollEvent(&event))
	    if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN)
		throw signal::UserQuitRequest();

	try
	{
	    int col = rand()%this->board->getNbColumns();
	    int line = rand()%this->board->getNbLines();
	 
	    int value = this->board->flipSquareIn(col,line);

	    return value;
	}
	catch(signal::AlreadyVisible){ continue; }
        catch(signal::AlreadyFound){ continue; }
    }
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
    for (it = this->recolls.begin() ; it < this->recolls.end() ; ++it)
        delete *it;
}

int PerfectComputer::chooseSquare()
{
    SDL_Delay(settings.show_duration/3);

    SDL_Event event;

    while(true)
    {
	// Makes sure user did not ask to quit
	while(SDL_PollEvent(&event))
	    if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN)
		throw signal::UserQuitRequest();

	try
	{
	    int col = rand()%this->board->getNbColumns();
	    int line = rand()%this->board->getNbLines();
	 
	    int value = this->board->flipSquareIn(col,line);

	    return value;
	}
	catch(signal::AlreadyVisible){ continue; }
        catch(signal::AlreadyFound){ continue; }
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
    
    // debug:
    int i=0;
    vector<Recollection*>::iterator it;
    for (it = this->recolls.begin() ; it < this->recolls.end() ; ++it){
        cerr<<"["<<i<<": (";
        if((*it)->getStatus()==CLEARED) cerr<<"e";
        else cerr<<(*it)->getPosition1()<<";"<<(*it)->getPosition2();
        cerr<<")] ";
        ++i;
    }
    cerr<<endl;
}

void PerfectComputer::seeFoundCouple(int value)
{
    this->recolls[value]->clearPosition(value);
}
