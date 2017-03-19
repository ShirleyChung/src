#include "../../classes/console.h"
#include "../../classes/loader.h"
#include "../../classes/configfile.h"

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

	ConfigFile conf("./conf/loadmodule.cfg");

	Console con;
	con.SetCmdCallback(test);

	Loader ldr("./libman.so");

	IModule* mod = ldr.GetModule();
	if( mod )
		cout<<mod->GetModuleDesc()<<"\n";

	con.Prompt();

	conf.Write("libman","./libman.so");

	return 0;
}
