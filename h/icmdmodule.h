#ifndef _module_interface_define_for_command_inpuit_2017_03
#define _module_interface_define_for_command_inpuit_2017_03

#include "imodule.h"
#include <vector>

typedef string (*OutputCallback)(string msg);

class ICmdModule: public IModule
{
protected:
	OutputCallback _outCb;
public:
	ICmdModule(){ _interfaceType |= I_COMMAND; }

	virtual bool SetOutputCallback(OutputCallback cb){ _outCb = cb; return true; }

/* Needs implement  */
	virtual string EnterCommandString(const std::vector<string>& cmd) = 0;
};

#endif
