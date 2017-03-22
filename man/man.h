#ifndef _manual_help_2017_module
#define _manual_help_2017_module

#include "../h/icmdmodule.h"
#include <map>
#include <list>

using namespace std;

class Man: public ICmdModule
{
	typedef bool (*CMD_PROC)(string);
	typedef map<string, CMD_PROC> CMD_MAP;

	static Man* _inst;
	OutputCallback _outCb;

	CMD_MAP _cmdMap;
	
public:
	Man();
	virtual string GetModuleDesc(){ return "Manual module"; }

	static IModule* GetModule(){
		return (_inst)? _inst: new Man();
	}

	virtual void EnterCommand(const vector<string>& cmd);
	
	list<string> GetSupportedCommands();
};

#endif
