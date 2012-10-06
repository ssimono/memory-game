#include "thread.h"

namespace thread
{
    int count_to_10(void* data)
    {
	bool* flag = (bool*)(data);
	
	for(int i=0; i<10; ++i)
	{
	    if( !(*flag) ) return 0;
	    std::cout<<i<<" sheeps"<<std::endl;
	    SDL_Delay(1000);
	}
	return 0;
    }
}

// Child classes definitions:

CountTo10::CountTo10()/*:Thread::Thread()*/
{
    this->function = thread::count_to_10;
}

// virtual class thread definitions:

Thread::Thread()
{
    std::cout<<"--- NEW THREAD ---"<<std::endl;
    this->status = thread::READY;
    this->flag = new bool(true);
}

Thread::~Thread()
{
    if( this->status == thread::RUNNING ) this->stop();
    delete this->flag;
}

void Thread::start()
{
    this->sdl_thread = SDL_CreateThread(this->function,this->flag);
    this->status = thread::RUNNING;
}

void Thread::stop()
{
    if( this->status != thread::RUNNING ) return;
    
    (*this->flag) = false;
    this->status = thread::STOPPING;
        
    SDL_WaitThread(this->sdl_thread,NULL);
        
    this->status = thread::STOPPED;
    
    std::cout<<"--- THREAD STOPPED ---"<<std::endl;
    
}