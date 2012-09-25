#include "square.h"

Square::Square(short id, short value)
{
    this->id = id;
    this->value = value;
}

short Square::getValue()
{
    return this->value;
}

short Square::getId()
{
    return this->id;
}