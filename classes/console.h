#ifndef _console_2017_03_cmd_input_12454
#define _console_2017_03_cmd_input_12454

#include <iostream>
#include "../h/common_def.h"

class Console
{
	CMDCBLIST _callbackList;
	list<string> 	_cmdHistory;
	string		_prompt, _cmd;

	bool _IsExitCmd(string);
	void _QueueCmd();

public:
	Console();
	virtual ~Console();

	void Prompt();
	void SetPrompt(string str){ if(str.size()) _prompt = str; }
	
	void AddCommandHandler(cmd_handler cb){ if(cb) _callbackList.push_back(cb); }
};

#endif
