#ifndef _manual_help_2017_module
#define _manual_help_2017_module

#include "../h/imodule.h"

class Man: public IModule
{
	static Man* _inst;
public:
	Man();
	virtual string GetModuleDesc(){ return "Manual module!"; }

	static IModule* GetModule(){
		return (_inst)? _inst: new Man();
	}
};

#endif
