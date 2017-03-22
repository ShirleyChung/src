#include "console.h"

#define MAX_HISTORY 200

Console::Console()
:_prompt(">")
{
}

Console::~Console()
{}

void Console::Prompt()
{
	do 
	{		
		for( CMDCBLIST::iterator i = _callbackList.begin(); i != _callbackList.end(); ++i )
			(*i)(GetTokens(_cmd));
		
		_QueueCmd();
		
		_cmd.clear();
		cout<<_prompt;
		getline( cin, _cmd );
	}
	while( !_IsExitCmd(_cmd) );

	cout<< "Bye!\n";
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
