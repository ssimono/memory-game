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
    
    while(true)
    {
        SDL_WaitEvent(&event);
        
        switch(event.type)
        {
            case SDL_QUIT:
                throw signal::UserQuitRequest();
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
