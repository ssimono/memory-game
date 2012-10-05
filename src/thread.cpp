#include "thread.h"

namespace thread
{
    int count_to_10(void* data)
    {
	for(int i=0; i<10; ++i)
	{
	    std::cout<<i<<" sheeps"<<std::endl;
	    SDL_Delay(5000);
	}	
	return 0;
    }
}

Thread::Thread()
{
    this->function = &thread::count_to_10;
    this->status = thread::READY;
}

Thread::~Thread()
{
    if( this->status == thread::RUNNING ) this->stop();
}

void Thread::start()
{
    this->sdl_thread = SDL_CreateThread(this->function,NULL);
    this->status = thread::RUNNING;
}

void Thread::stop()
{
    if( this->status != thread::RUNNING ) return;
    
    this->status = thread::STOPPING;
    SDL_WaitThread(this->sdl_thread,NULL);
    this->status = thread::STOPPED;
}