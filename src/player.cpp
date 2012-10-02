#include <iostream>

#include "player.h"

Player::Player(Board* board)
{
    this->board = board;
}

bool Player::play()
{
    try
    {
        SquarePosition chosen_square = this->chooseSquare();
        this->board->flipSquareIn(chosen_square.column, chosen_square.line);
        
        return true;
    }
    catch(int i)
    {
        std::cerr<<"chooseSquare thrown an exception ("<<i<<"), returning"<<std::endl;
        return false;
    }
}

SquarePosition Player::chooseSquare()
{
    SDL_Event event;
    
    while(true)
    {
        SDL_WaitEvent(&event);
        
        switch(event.type)
        {
            case SDL_QUIT:
                throw 1;
                break;
            case SDL_KEYDOWN:
                throw 2;
                break;
            case SDL_MOUSEBUTTONDOWN:
                using namespace std;
                cout<<"Un clic ("<<event.button.x<<','<<event.button.y<<')'<<endl;
                try
                {
                    SquarePosition pos = this->board->findSquare(event.button.x, event.button.y);
                    return pos;
                }
                catch(int i)
                {
                    cerr<<"Exception reçue : "<<i<<endl;
                }
            default:
                continue;
        }
    }
}