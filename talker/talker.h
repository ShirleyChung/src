#ifndef _talker_for_funny_chat_using_pthread_2017
#define _talker_for_funny_chat_using_pthread_2017

#include <thread>

#include "../classes/funcdisp.h"

class Talker: public FuncDisp<Talker>
{
	static Talker* _inst;
	thread _thd;
	static void thread_proc(Talker*);

	void Hello(STRARR&);
	bool _run;
public:
	Talker();
	virtual ~Talker();
	string GetModuleDesc(){ return "Talker v0.0.0.1"; }
	
	static IModule* GetModule(){
		return (_inst)? _inst: new Talker();
	}
};

#endif
