#include "../../classes/console.h"
#include "../../classes/loader.h"

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

	Loader ldr("./libMan.so");

	IModule* mod = ldr.GetModule();
	if( mod )
		cout<<mod->GetModuleDesc()<<"\n";

	con.Prompt();

	return 0;
}
