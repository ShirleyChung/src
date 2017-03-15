#ifndef _console_2017_03_cmd_input_12454
#define _console_2017_03_cmd_input_12454

#include <iostream>
#include <list>

using namespace std;

class Console
{
	list<string> _cmdHistory;
public:
	Console();
	virtual ~Console();

	void Prompt();
};

#endif
