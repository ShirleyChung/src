#ifndef _mud_module_mudgaming_world_2017_04
#define _mud_module_mudgaming_world_2017_04

#include "funcdisp.hpp"
#include "singleton.hpp"

#include "world.h"

class Mud:public FuncDisp<Mud>
{
public:
	Mud();
	virtual ~Mud();

	string GetModuleDesc(){ return "MUD Module"; }
};

#endif
