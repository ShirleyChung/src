#ifndef _console_2017_03_cmd_input_12454
#define _console_2017_03_cmd_input_12454

#include <iostream>
#include <list>
#include <vector>

using namespace std;

typedef void (*cmd_callback)(const vector<string>&);

class Console
{
	list<string> 	_cmdHistory;
	string		_prompt, _cmd;

	bool _IsExitCmd(string);
	void _QueueCmd();

	cmd_callback	_cbCommand;

public:
	Console();
	virtual ~Console();

	void Prompt();
	void SetPrompt(string str){ if(str.size()) _prompt = str; }
	void SetCmdCallback(cmd_callback cb){ _cbCommand = cb; }

	vector<string> GetTokens(string line);
};

#endif
