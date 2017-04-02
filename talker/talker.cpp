#include "talker.h"
#include <stdlib.h>
#include <chrono>

extern "C" IModule* GetModule()
{
	return Singleton<Talker>::GetInstance();
}

Talker::Talker()
:_thd(thread_proc, this)
,_run(true)
{
	_name = "talker";
	AddFunc("hello", &Talker::Hello);
}

Talker::~Talker()
{
	_run = false;
}

void Talker::Hello(STRARR& cmd)
{
	cout<< "Hi!\n";
}

void Talker::thread_proc(Talker* pthis)
{
	while(pthis->_run)
	{
		cout<<"hello!"<<rand()<<" \n";
		int wait = 500 + rand()%5000;
		this_thread::sleep_for(std::chrono::milliseconds(wait));
	}
}
