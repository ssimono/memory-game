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
	
	enum RecollStatus setPosition(int position, int value);
        void clearPosition(int value);
        
        int getPosition1();
        int getPosition2();
        enum RecollStatus getStatus();
        
    private:
	int Value;
        int Position1;
        int Position2;
        enum RecollStatus Status;
};

#endif

