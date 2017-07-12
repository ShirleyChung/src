#ifndef _artificial_neual_network_simulation_module_2017_05_shirley_
#define _artificial_neual_network_simulation_module_2017_05_shirley_

#include "funcdisp.hpp"
#include "singleton.hpp"

#include <list>
using namespace std;

/* 定義神經元 */
struct Neural{
    double multiply;
    string key, val;
    list<Neural*> connect;
};

/* 神經網路模組 */
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
