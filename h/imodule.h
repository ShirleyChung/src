#ifndef _module_interface_define_2017_03_shirley
#define _module_interface_define_2017_03_shirley

#include <string>

enum _INTERFACE_TYPE
{
	I_COMMAND 	= 0x0001,
	I_UI 		= 0x0002,
	I_FUNCTION 	= 0x0004,
};

using namespace std;

class IModule
{
protected:
	int _interfaceType;
public:
	virtual string GetModuleDesc() = 0;
	virtual int GetSupportedInterfaceType(){ return _interfaceType; }
};

#endif
