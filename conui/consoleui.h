#ifndef _console_ui_new_for_mud_control_browse_command_and_viewing_201704
#define _console_ui_new_for_mud_control_browse_command_and_viewing_201704

#include "funcdisp.hpp"
#include "singleton.hpp"

class ConsoleUI: public FuncDisp<ConsoleUI>
{

public:
	ConsoleUI();
	virtual ~ConsoleUI();
	
	virtual string GetModuleDesc(){ return "Console UI v0.0.0.1";}

};

#endif