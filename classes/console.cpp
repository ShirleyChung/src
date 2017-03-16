#include "console.h"

#define MAX_HISTORY 200

Console::Console()
:_prompt(">"), _cbCommand(0)
{
}

Console::~Console()
{}

void Console::Prompt()
{
	while( !_IsExitCmd(_cmd) ) 
	{
		_cmd.clear();
		cout<<_prompt;
		getline( cin, _cmd );

		if (_cbCommand) (*_cbCommand)(GetTokens(_cmd));
		
		_QueueCmd();
	}

	cout<< "Bye!";
}

bool Console::_IsExitCmd(string cmd)
{
	if (cmd == "exit")
		return true;

	return false;
}

void Console::_QueueCmd()
{
	
	_cmdHistory.push_back(_cmd);
	if (_cmdHistory.size() > MAX_HISTORY)
		_cmdHistory.pop_front();
}

#define SEP ' '
vector<string> Console::GetTokens(string line)
{
	vector<string> list;
	size_t pos = 0, curpos = 0;
	while( curpos != string::npos)
	{
		curpos = line.find(SEP, pos);
		string tok = (curpos == string::npos)? line.substr(pos): line.substr(pos, curpos - pos);

		if (tok.size())
			list.push_back( tok );
		
		pos = curpos + 1;
	}
	return list;
}
