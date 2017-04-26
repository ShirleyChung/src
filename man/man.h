#ifndef _manual_help_2017_module
#define _manual_help_2017_module

#include "../classes/funcdisp.hpp"
#include "../classes/singleton.hpp"

using namespace std;

class Man: public FuncDisp<Man>
{
	void Help(STRARR&);

	void Manual(STRARR&);
	
	string _desc;
	
public:
	Man();

	virtual string GetModuleDesc(){ return _desc; }
};

typedef Singleton<Man> ManSingleton;

#endif
