#ifndef _console_2017_03_cmd_input_12454
#define _console_2017_03_cmd_input_12454

#include <iostream>
#include <list>

using namespace std;

class Console
{
	list<string> 	_cmdHistory;
	string		_prompt, _cmd;

	bool IsExitCmd(string);

public:
	Console();
	virtual ~Console();

	void Prompt();
	void SetPrompt(string str){ if(str.size()) _prompt = str; }
};

#endif
