#include "man.h"
#include <iostream>

Man* Man::_inst = 0;

extern "C" IModule* GetModule()
{
	return Man::GetModule();
}

Man::Man()
{
	_cmdMap["help"] = NULL;
}

string Man::EnterCommandString(const vector<string>& args)
{
	string& cmd = args[0];

	if (cmd == "help")
	{
		CMD_MAP::iterator i = _cmdMap.begin();
		while(i != _cmdMap.end())
			cout<<i++->first<<"\n";
	}
	else
	{
		cout<<"analyzing '"<<cmd<<"' ...\n";
		cout<<"Sorry, I dont know what '"<<cmd<<"' means.\n";
	}
	return "command execute ok.\n";
}

list<string> Man::GetSupportedCommands()
{
	list<string> ret;

	CMD_MAP::iterator i = _cmdMap.begin();
	for(; i != _cmdMap.end(); ++i)
		ret.push_back(i->first);

	return ret;
}	
