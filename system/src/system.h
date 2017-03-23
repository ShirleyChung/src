#ifndef _system_obj_for_basic_interface_console_and_control_mediator_2017
#define _system_obj_for_basic_interface_console_and_control_mediator_2017

#include "../../classes/console.h"
#include "../../classes/funcdisp.h"
#include "../../classes/configfile.h"

class System:public FuncDisp<System>
{
	Loader _ldr;
	Console _con;
	ConfigFile _conf;
	
	void ListModule(STRARR&);

	void LoadModule(STRARR&);

public:
	System();
	virtual ~System();

	virtual string GetModuleDesc(){ return "system mediator.\n"; }
	
	void Run();
	void AddCmdHandler(cmd_handler cb){ _con.AddCommandHandler(cb); }
};

#endif