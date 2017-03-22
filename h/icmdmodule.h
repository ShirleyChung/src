#ifndef _module_interface_define_for_command_inpuit_2017_03
#define _module_interface_define_for_command_inpuit_2017_03

#include "imodule.h"
#include <vector>

typedef void (*OutputCallback)(string msg);

class ICmdModule: public IModule
{
protected:
	OutputCallback _outCb;
public:
	ICmdModule(){ _interfaceType |= I_COMMAND; }

	virtual void SetOutputCallback(OutputCallback cb){ _outCb = cb; }
	
/* Needs implement  */
	virtual void EnterCommand(const std::vector<string>& cmd) = 0;
};

#endif
