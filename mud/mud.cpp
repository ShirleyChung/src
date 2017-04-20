#include "mud.h"


extern "C" IModule* GetModule()
{
	return Singleton<Mud>::GetInstance();
}

Mud::Mud()
{

}

Mud::~Mud()
{
}
