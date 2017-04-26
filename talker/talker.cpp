#include "talker.h"
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <ctime>

extern "C" IModule* GetModule()
{
	return Singleton<Talker>::GetInstance();
}

Talker::Talker()
:_run(true)
,_conf("./conf/talker.cfg")
{
	_name = "talker";
	AddFunc("hello", &Talker::Hello);
	AddFunc("setdict", &Talker::SetDict);
	AddFunc("murmur", &Talker::StartThread);
	AddFunc("shutup", &Talker::CloseThread);
	
	if (_conf["dictpath"].size())
		loadWords(_conf["dictpath"]);
}

Talker::~Talker()
{
	cout<<"\n~talker\n";
	_run = false;
}


void Talker::run()
{
	while(_run)
	{
		cout<<say()<<" \n";
		long wait = 500 + rand()%5000;
		usleep(wait*1000);
	}
}

void Talker::loadWords(const string& fn)
{
	ifstream ifs(fn.c_str());
	if(!ifs){
		cout<<"cannot read "<<fn<<'\n';
		return;
	}
	else 
		cout<<"words "<< fn <<" load ok\n";
	
	_conf.Add("dictpath", fn);
		
	_words.clear();

	string line;
	int ipos = 0;
	while(getline(ifs, line))
		_words.push_back(line);
	
}

string Talker::say()
{
	int nwords = _words.size();
	if (!nwords) return "No words.";
	
	srand(time(NULL));
	int index = rand() % nwords;
	
	return _words[index];
	
}

void Talker::Hello(STRARR& cmd)
{
	cout<< "Hi! "<<say()<<'\n';
}

void Talker::SetDict(STRARR& cmd)
{
	if (cmd.size())
	{
		loadWords(cmd[0]);
		_conf.Save();
	}
	else
		cout<<"usage: setdict [words file path]\n";
}

void Talker::StartThread(STRARR& cmd)
{
	start();
}

void Talker::CloseThread(STRARR& cmd)
{
	stop();
	cout<<"Talker stop talking.\n";
}
