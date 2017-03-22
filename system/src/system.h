#ifndef _system_obj_for_basic_interface_console_and_control_mediator_2017
#define _system_obj_for_basic_interface_console_and_control_mediator_2017

#include "../../classes/console.h"
#include "../../classes/loader.h"
#include "../../classes/configfile.h"
#include "../../h/icmdmodule.h"

class System:public ICmdModule
{
	typedef void(System::*funcptr)(STRARR&);
	typedef map<string, funcptr> FUNCMAP;
	
	Loader _ldr;
	Console _con;
	ConfigFile _conf;
	
	void ListModule(STRARR&);

	void LoadModule(STRARR&);

	bool EnterCommandToModule(STRARR&);

	void ShowSupportedCmds();

	FUNCMAP _func_map;
public:
	System();
	virtual ~System();
	virtual void EnterCommand(STRARR& cmd);
	virtual string GetModuleDesc(){ return "system mediator.\n"; }
	
	void Run();
	void AddCmdHandler(cmd_handler cb){ _con.AddCommandHandler(cb); }
};

#endif