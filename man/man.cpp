#include "man.h"

Man* Man::_inst = 0;

extern "C" IModule* GetModule()
{
	return Man::GetModule();
}

Man::Man()
{
}
