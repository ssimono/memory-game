#ifndef THREAD_H
#define THREAD_H

#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

namespace thread{
    
    /**
     * Differents status a thread can have
     */
    enum Status
    {
	READY,
	RUNNING,
	STOPPING,
	STOPPED
    };
}

/**
 * A virtual class for managing threads
 */
class Thread
{
    public:
	Thread();
	~Thread();
	
	virtual void start();
	void stop();
	thread::Status getStatus();
	
    protected:
	SDL_Thread* sdl_thread;
	int (*function)(void *);
	thread::Status status;
	bool* flag;
};

/*
 * Class to test my Thread class framework
 */
class CountTo10:public Thread
{
    public:CountTo10();
};

#endif