#include <iostream>

#include "game.h"

Game::Game(SDL_Surface* screen)
{
    this->screen = screen;
}

Game::~Game()
{
    for(PlayerList::iterator it = this->players.begin();
	it != this->players.end(); ++it
    ) delete *it;

    this->players.clear();
}

int Game::getNbPlayers()
{
    return this->players.size();
}

void Game::addPlayer(Player* player)
{
    this->players.push_back(player);
    this->currentPlayer = this->players.begin();
}

void Game::start()
{
    if( this->getNbPlayers() == 0 ) throw error::NoPlayers();
    
    try
    {	
	while(true)
	{
	    while( (*this->currentPlayer)->play() ) (*this->currentPlayer)->inscreaseScore();
	    
	    if( ++this->currentPlayer == this->players.end() )
		this->currentPlayer = this->players.begin();
	}
    }
    catch(signal::BoardComplete)
    {
	(*this->currentPlayer)->inscreaseScore();
	
	using namespace std;
	
	cout<<"End of Game"<<endl;
	cout<<"-----------"<<endl;
	
	int i=0;
	for(PlayerList::iterator it = this->players.begin();
	it != this->players.end(); ++it){
	    cout<<(*it)->getName()<<":\t"<<(*it)->getScore()<<" points"<<endl;
	}
    }
}