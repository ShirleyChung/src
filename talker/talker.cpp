#include "talker.h"
#include <stdlib.h>
#include <unistd.h>

extern "C" IModule* GetModule()
{
	return Singleton<Talker>::GetInstance();
}

Talker::Talker()
:_run(true)
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

void* Talker::thread_proc(void* pt)
{
	Talker* pthis = (Talker*)pt;
	while(pthis->_run)
	{
		cout<<"hello!"<<rand()<<" \n";
		int wait = 500 + rand()%5000;
		usleep(wait);
	}
	return pt;
}
