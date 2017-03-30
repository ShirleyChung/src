#ifndef _module_interface_define_for_command_inpuit_2017_03
#define _module_interface_define_for_command_inpuit_2017_03

#include "imodule.h"
#include <vector>

typedef void (*OutputCallback)(string msg);

class ICmdModule: public IModule
{
protected:
	OutputCallback _outCb;
	void Invoke(const string& cmd){ if(_outCb) _outCb(cmd); }
	
public:
	ICmdModule():_outCb(NULL){ _interfaceType |= I_COMMAND; }

	virtual void SetOutputCallback(OutputCallback cb){ _outCb = cb; }
	virtual vector<string> GetCommands(){ return vector<string>(); }
	
/* Needs implement  */
	virtual bool EnterCommand(const std::vector<string>& cmd) = 0;
};

#endif
