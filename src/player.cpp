#include <iostream>

#include "player.h"

Player::Player(Board* board)
{
    this->board = board;
    this->score = 0;
}

void Player::getPoint()
{
    this->score++;
}

bool Player::play()
{
    try
    {
        // First tour:
        int first_value = this->chooseSquare();
        
        // Second tour:
        int second_value = this->chooseSquare();
        
        return (first_value == second_value);
    }
    catch(int i)
    {
        std::cerr<<"chooseSquare thrown an exception ("<<i<<"), returning"<<std::endl;
        return false;
    }
}

int Player::chooseSquare()
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
                cout<<"Click ("<<event.button.x<<','<<event.button.y<<')'<<endl;
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
