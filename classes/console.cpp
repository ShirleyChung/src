#include "console.h"

Console::Console()
:_prompt(">")
{
}

Console::~Console()
{}

void Console::Prompt()
{
	cout<<_prompt;
	
	while( !IsExitCmd(_cmd) ) 
	{
		_cmd.clear();
		cin>>_cmd;
		_cmdHistory.push_back(_cmd);
	}

	cout<< "Bye!";
}

bool IsExitCmd(string cmd)
{
	if (cmd == "exit")
		return true;

	return false;
}
