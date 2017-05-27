#ifndef _artificial_neual_network_simulation_module_2017_05_shirley_
#define _artificial_neual_network_simulation_module_2017_05_shirley_

#include "funcdisp.hpp"
#include "singleton.hpp"

struct Neural{
	double weight;
};

class AnnMind:public FuncDisp<AnnMind>
{
	void Trainning(STRARR&);
	
	string _desc;
	
public:
	AnnMind();
	virtual~ AnnMind();
	
	virtual string GetModuleDesc(){ return _desc; }
};

typedef Singleton<AnnMind> AnnMindSingleton;

#endif
