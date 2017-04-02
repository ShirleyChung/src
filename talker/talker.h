#ifndef _talker_for_funny_chat_using_pthread_2017
#define _talker_for_funny_chat_using_pthread_2017

#include "../classes/funcdisp.hpp"
#include "../classes/singleton.hpp"
#include <thread>

class Talker: public FuncDisp<Talker>
{
	thread _thd;
	static void thread_proc(Talker*);

	void Hello(STRARR&);
	bool _run;
public:
	Talker();
	virtual ~Talker();
	string GetModuleDesc(){ return "Talker v0.0.0.1"; }
};

#endif
