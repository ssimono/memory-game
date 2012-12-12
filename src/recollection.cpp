#include "recollection.h"
#include "game_exception.h"

Recollection::Recollection(int value)
{
    this->Value = value;
    this->Status = EMPTY;
    this->Position1 = this->Position2 = -1;
}

int Recollection::getPosition1(){ return this->Position1; }
int Recollection::getPosition2(){ return this->Position2; }
RecollStatus Recollection::getStatus(){ return this->Status; }

RecollStatus Recollection::setPosition(int position, int value)
{
    // Check we are setting a position to the right valued square:
    if(value != this->Value) throw error::WrongValue();
    
    if(this->Status == EMPTY)
    {
        this->Position1 = position;
        this->Status = HALF;
        return this->Status;
    }
    
    if(this->Status == HALF)
    {
        if(position != this->Position1)
        {
            this->Position2 = position;
            this->Status = MATCHED;
            return this->Status;
        }
        else return HALF;
    }
}

void Recollection::clearPosition(int value)
{
    // Check we are clearing a position to the right valued square:
    if(value != this->Value) throw error::WrongValue();
    
    this->Status = CLEARED;
}