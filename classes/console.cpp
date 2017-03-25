#include "console.h"
#include "tool.h"

#define MAX_HISTORY 200

#define ckey "prompt"

Console::Console()
:_conf("conf/console.cfg")
{
	_prompt = _conf.GetValue(ckey);
	if (!_prompt.size()) _prompt = '>';
	_conf.Add(ckey, _prompt);
}

Console::~Console()
{
	_conf.Save();
}

void Console::Prompt()
{
	do 
	{		
		for( CMDCBLIST::iterator i = _callbackList.begin(); i != _callbackList.end(); ++i )
			(*i)(Tokenize(_cmd));
		
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
