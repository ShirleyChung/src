#include "system.h"

System sys;

void CmdHandler(STRARR& cmd)
{
	sys.EnterCommand(cmd);
}

System::System()
:_conf("./conf/loadmodule.cfg")
,FuncDisp<System>(_ldr)
{
	_ldr.Load(_conf.GetConfig());
	
	_func_map["listmod"] = &System::ListModule;
	_func_map["loadmod"] = &System::LoadModule;
	
	_con.AddCommandHandler(CmdHandler);
}

System::~System()
{

}

void System::Run()
{
	_con.Prompt();
}

void System::ListModule(STRARR&)
{
	vector<string> modlist = _ldr.GetModuleList();
	for( vector<string>::iterator i = modlist.begin(); i != modlist.end(); ++i)
		cout<<*i<<" = "<<_ldr.GetModule(*i)->GetModuleDesc()<<'\n';
}

void System::LoadModule(STRARR& cmd)
{
	if (cmd.size())
		_ldr.Load(cmd[0]);
	else
		cout<<"please specify module path\n";
}

int main(int argc, char* argv[])
{
	std::cout<<"system\n";
	
	sys.Run();

	return 0;
}
