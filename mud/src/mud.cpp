#include "mud.h"


extern "C" IModule* GetModule()
{
	return Singleton<Mud>::GetInstance();
}

Mud::Mud()
{
	_name = "MUD";
}

Mud::~Mud()
{
}
