#ifndef _artificial_neual_network_simulation_module_2017_05_shirley_
#define _artificial_neual_network_simulation_module_2017_05_shirley_

#include "funcdisp.hpp"
#include "singleton.hpp"

#include <list>
using namespace std;

/* �w�q���g�� */
struct Neural{
    double multiply;
    string key, val;
    list<Neural*> connect;
};

/* ���g�����Ҳ� */
class AnnMind:public FuncDisp<AnnMind>
{
	void Trainning(STRARR&);
	
	string _desc;
	list<Neural> _neulist;

public:
	AnnMind();
	virtual~ AnnMind();
	
	virtual string GetModuleDesc(){ return _desc; }
};

typedef Singleton<AnnMind> AnnMindSingleton;

#endif
