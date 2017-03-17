#ifndef _module_interface_define_2017_03_shirley
#define _module_interface_define_2017_03_shirley

#include <string>

using namespace std;

class IModule
{
public:
	virtual string GetModuleDesc() = 0;
};

#endif
