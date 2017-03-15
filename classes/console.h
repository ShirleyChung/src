#ifndef _console_2017_03_cmd_input_12454
#define _console_2017_03_cmd_input_12454

#include <iostream.h>
#include <list>

class Console
{
	std::list<string> _cmdHistory;
public:
	Console();
	virtual ~Console();

	void Prompt();
};

#endif
