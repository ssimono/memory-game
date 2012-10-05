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
        
    int count_to_10(void* data);
}

/**
 * A class for managing threads
 */
class Thread
{
    public:
	Thread();
	~Thread();
	
	void start();
	void stop();
	thread::Status getStatus();
	
    private:
	SDL_Thread* sdl_thread;
	int (*function)(void *);
	thread::Status status;
};

#endif