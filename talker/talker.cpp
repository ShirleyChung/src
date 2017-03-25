#include "talker.h"
#include <stdlib.h>
#include <chrono>

Talker* Talker::_inst = 0;

extern "C" IModule* GetModule()
{
	return Talker::GetModule();
}

Talker::Talker()
:_thd(thread_proc, this)
{
}

Talker::~Talker()
{
}

void Talker::thread_proc(Talker* pthis)
{
	while(1)
	{
		cout<<"hello!"<<rand()<<" \n";
		int wait = 500 + rand()%5000;
		this_thread::sleep_for(std::chrono::milliseconds(wait));
		//this_thread::sleep_until(wait);
	}
}
