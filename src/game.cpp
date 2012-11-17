#include <iostream>
#include <string>
#include <sstream>

#include <SDL/SDL_ttf.h>

#include "config.h"
#include "game_exception.h"
#include "game.h"

static TTF_Font* font = NULL;

Game::Game(SDL_Surface* screen)
{
    this->screen = screen;
    
    font=TTF_OpenFont("share/NobileFont/nobile.ttf", 20);
    if(!font)	throw GameException( std::string(TTF_GetError()) );

    this->board.init(this->screen, NB_LINES, NB_COLUMNS);
}

Game::~Game()
{
    for(PlayerList::iterator it = this->players.begin();
	it != this->players.end(); ++it
    ) delete *it;

    this->players.clear();
    
    TTF_CloseFont(font);
    font=NULL;
}

int Game::getNbPlayers()
{
    return this->players.size();
}

void Game::updateScorePanel()
{
    SDL_Rect score_panel;
    score_panel.x = NB_COLUMNS * (SQUARE_WIDTH + SQUARE_MARGIN_RIGHT) + BOARD_ORIGIN_X;
    score_panel.y = BOARD_ORIGIN_Y;
    score_panel.w = SCORE_PANEL_WIDTH;
    score_panel.h = this->getNbPlayers() * SCORE_PANEL_HEIGHT;
    
    SDL_FillRect(screen, &score_panel, BACKGROUND_COLOR);
    SDL_Color black={0,0,0};
    SDL_Color grey ={0xb8,0xb8,0xb8};
    
    SDL_Surface *text_surface;
    
    SDL_Rect score_area = score_panel;
    score_area.h = SCORE_PANEL_HEIGHT;
    score_area.y -= SCORE_PANEL_HEIGHT; // Start with 'minus height' so it will be 0 at first loop
    
    for(PlayerList::iterator it = this->players.begin();
	it != this->players.end(); ++it){
	
	std::ostringstream text;
	text<<(*it)->getName()<<" ("<<(*it)->getScore()<<')';
	
	SDL_Color color = (it == this->currentPlayer)? black : grey;
	
	if( !(text_surface=TTF_RenderText_Solid( font, text.str().c_str(), color )) )
	throw GameException( std::string(TTF_GetError()) );

	score_area.y += SCORE_PANEL_HEIGHT;
	SDL_BlitSurface(text_surface, NULL, this->screen, &score_area);
		
	SDL_FreeSurface(text_surface);
    }
    
    SDL_UpdateRect(this->screen, score_panel.x,score_panel.y,score_panel.w,score_panel.h);
}

void Game::addPlayer(Player* player)
{
    player->setBoard(&this->board);
    this->players.push_back(player);
    this->currentPlayer = this->players.begin();
}

void Game::start()
{
    if( this->getNbPlayers() == 0 ) throw error::NoPlayers();
    
    this->updateScorePanel();
    
    try
    {	
	while(true)
	{	    
	    while( (*this->currentPlayer)->play() )
	    {
		(*this->currentPlayer)->inscreaseScore();
		this->updateScorePanel();
	    }
	    
	    if( ++this->currentPlayer == this->players.end() )
		this->currentPlayer = this->players.begin();
	    
	    this->updateScorePanel();
	}
    }
    catch(signal::BoardComplete)
    {
	(*this->currentPlayer)->inscreaseScore();
	
	using namespace std;
	
	cout<<"End of Game"<<endl;
	cout<<"-----------"<<endl;
	
	for(PlayerList::iterator it = this->players.begin();
	it != this->players.end(); ++it){
	    cout<<(*it)->getName()<<":\t"<<(*it)->getScore()<<" points"<<endl;
	}
    }
}
