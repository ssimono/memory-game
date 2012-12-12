#ifndef RECOLLECTION_H
#define	RECOLLECTION_H

enum RecollStatus
{
    EMPTY,
    HALF,
    MATCHED,
    CLEARED
};

class Recollection
{
    public:
	Recollection(int value);
	
	RecollStatus setPosition(int position, int value);
        void clearPosition(int value);
        
        int getPosition1();
        int getPosition2();
        RecollStatus getStatus();
        
    private:
	int Value;
        int Position1;
        int Position2;
        RecollStatus Status;
};

#endif

