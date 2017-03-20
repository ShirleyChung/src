#include "../../classes/console.h"
#include "../../classes/loader.h"
#include "../../classes/configfile.h"
#include "../../h/icmdmodule.h"


ICmdModule* mod;

void input(const vector<string>& args)
{
	if (args.size())
		mod->EnterCommandString();
}

int main(int argc, char* argv[])
{
	std::cout<<"system\n";

	ConfigFile conf("./conf/loadmodule.cfg");

	Console con;

	Loader ldr("./libman.so");

	mod = (ICmdModule*)ldr.GetModule();
	if( mod )
		cout<<mod->GetModuleDesc()<<"\n";

	con.SetCmdCallback(input);

	con.Prompt();

	conf.Write("libman","./libman.so");

	return 0;
}
