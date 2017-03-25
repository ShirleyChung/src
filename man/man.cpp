#include "man.h"
#include "../classes/tool.h"
#include <iostream>

Man* Man::_inst = 0;

extern "C" IModule* GetModule()
{
	return Man::GetModule();
}

Man::Man()
{
	_desc = "Manual module";
	AddFunc("help", &Man::Help);
	AddFunc("man", &Man::Manual);
	
}

void Man::Help(STRARR& cmd)
{
	cout<<"I come to help!\n";
}

void Man::Manual(STRARR& cmd)
{
	if (cmd.size())
	{
		if (cmd[0] == "setdesc" && cmd.size() > 1)
		{
			_desc = Tokencombine( STRARR(cmd.begin()+1, cmd.end()) );
			Invoke("listmod");
		}
		else
			cout<< "usage : man setdesc [what u want to set]\n";
	}
}