#ifndef _talker_for_funny_chat_using_pthread_2017
#define _talker_for_funny_chat_using_pthread_2017

#include "../classes/funcdisp.hpp"
#include "../classes/singleton.hpp"
#include "../classes/thread.hpp"
#include "../classes/configfile.h"

#include <vector>

using namespace std;

class Talker: public FuncDisp<Talker>, public Thread
{
	bool _run;
	vector<string> _words;
	ConfigFile _conf;

	void loadWords(const string& fn);

	string say();
	
	void Hello(STRARR&);
	void SetDict(STRARR&);
	void StartThread(STRARR&);
	void CloseThread(STRARR&);
public:
	Talker();
	virtual ~Talker();
	string GetModuleDesc(){ return "Talker v0.0.0.1"; }
	
	void run();
};

#endif
