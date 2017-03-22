#include "system.h"

System sys;

void CmdHandler(STRARR cmd)
{
	sys.EnterCommand(cmd);
}

System::System()
:_conf("./conf/loadmodule.cfg")
{
	_ldr.Load(_conf.GetConfig());
	
	_func_map["listmod"] = &System::ListModule;
	
	_con.AddCommandHandler(CmdHandler);
}

System::~System()
{

}

void System::EnterCommand(STRARR cmd)
{
	if (cmd.size())
	{
		FUNCMAP::iterator i = _func_map.find(cmd[0]);
		if (i == _func_map.end())
			cout<<" I don't know what '"<< cmd[0] <<"' means.\n";
		else
			(this->*(i->second))();
	}
}

void System::Run()
{
	_con.Prompt();
}

void System::ListModule()
{
	vector<string> modlist = _ldr.GetModuleList();
	for( vector<string>::iterator i = modlist.begin(); i != modlist.end(); ++i)
		cout<<*i<<" = "<<_ldr.GetModule(*i)->GetModuleDesc()<<'\n';
}

int main(int argc, char* argv[])
{
	std::cout<<"system\n";
	
	sys.Run();

	return 0;
}
