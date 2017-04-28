#ifndef _system_obj_for_basic_interface_console_and_control_mediator_2017
#define _system_obj_for_basic_interface_console_and_control_mediator_2017

#include "console.h"
#include "funcdisp.hpp"
#include "configfile.h"

class System:public FuncDisp<System>
{
	Loader _ldr;
	Console _con;
	ConfigFile _aliasconf;
	
	void ListModule(STRARR&);

	void LoadModule(STRARR&);
	void UnLoadModule(STRARR&);

	void SetPrompt(STRARR&);
	void Alias(STRARR&);
	
	void SetModuleOutputCallback(OutputCallback);

	void LoadAlias();
	void SaveAlias();

public:
	System();
	virtual ~System();

	virtual string GetModuleDesc(){ return "system mediator.\n"; }
	
	void Run();
	void AddCmdHandler(cmd_handler cb){ _con.AddCommandHandler(cb); }
};

#endif
