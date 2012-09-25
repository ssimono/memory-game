#ifndef SQUARE_H
#define SQUARE_H

const int SQUARE_WIDTH  = 70;
const int SQUARE_HEIGHT = 70;


class Square
{
    public:
	Square(short id, short value);
	
	short getId();
	short getValue();
	
    private:
	short id;
	short value;
};

#endif