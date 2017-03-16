#include "../classes/console.h"

void test(const vector<string>& args)
{
	vector<string>::const_iterator i = args.begin();
	while( i != args.end() )
	{
		cout<< *i << '\n';
		i++;
	}
}

int main(int argc, char* argv[])
{
	std::cout<<"system\n";

	Console con;
	con.SetCmdCallback(test);

	con.Prompt();

	return 0;
}
