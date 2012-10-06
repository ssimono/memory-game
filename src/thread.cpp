#include "thread.h"

namespace thread
{
    namespace count_to_10
    {
	bool flag;
	
	int function(void* data)
	{
	    for(int i=0; i<10; ++i)
	    {
		if( !(count_to_10::flag) ) break;
		std::cout<<i<<" sheeps"<<std::endl;
		SDL_Delay(5000);
	    }	
	    return 0;
	}
    }
}

Thread::Thread()
{
    this->status = thread::READY;
}

Thread::~Thread()
{
    if( this->status == thread::RUNNING ) this->stop();
}

void Thread::start()
{
    (*this->flag) = true;
    this->sdl_thread = SDL_CreateThread(this->function,NULL);
    this->status = thread::RUNNING;
}

void Thread::stop()
{
    if( this->status != thread::RUNNING ) return;
    
    (*this->flag) = false;
    this->status = thread::STOPPING;
    SDL_WaitThread(this->sdl_thread,NULL);
    this->status = thread::STOPPED;
    
    std::cout<<"A thread just stopped"<<endl;
}

// Child classes definitions:

CountTo10::CountTo10():Thread::Thread()
{
    using namespace thread;

    this->function = &count_to_10::function;
    this->flag = &count_to_10::flag;
}