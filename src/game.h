#ifndef GAME_H
#define GAME_H

#include <list>

#include <SDL/SDL.h>

#include "player.h"

typedef std::list<Player*> PlayerList;

class Game
{
    public:
	Game(SDL_Surface* screen);
	~Game();
	
	void addPlayer(Player* player);
	void start();
	
	int getNbPlayers();
	
    private:
	void updateScorePanel();
	
	Board board;
	PlayerList players;
	PlayerList::iterator currentPlayer;
	
	SDL_Surface* screen;
};

#endif
