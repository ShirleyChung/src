#include "system.h"

System sys;

void CmdHandler(STRARR& cmd)
{
	sys.EnterCommand(cmd);
}

System::System()
:_conf("./conf/loadmodule.cfg")
{
	_ldr.Load(_conf.GetConfig());
	
	_func_map["listmod"] = &System::ListModule;
	_func_map["loadmod"] = &System::LoadModule;
	
	_con.AddCommandHandler(CmdHandler);
}

System::~System()
{

}

void System::EnterCommand(STRARR& cmd)
{
	if (cmd.size())
	{
		FUNCMAP::iterator i = _func_map.find(cmd[0]);
		if (i == _func_map.end())
		{
			if (!EnterCommandToModule(cmd))
				ShowSupportedCmds();
		}
		else
			(this->*(i->second))( vector<string>( cmd.begin()+1, cmd.end() )  );
	}
}

void System::ShowSupportedCmds()
{
	cout<<"Supported command:\n";
	for( FUNCMAP::iterator i = _func_map.begin(); i != _func_map.end(); ++i )
		cout<< '\t' << i->first << '\n';
}


bool System::EnterCommandToModule(STRARR& cmd)
{
	bool bHasCmd = false;
	STRARR arr = _ldr.GetModuleList();
	for( STRARR::const_iterator i = arr.begin(); i != arr.end(); ++i )
	{
		IModule* mod = _ldr.GetModule(*i);
		if (mod->GetSupportedInterfaceType() & I_COMMAND)
		{
			bHasCmd = true;
			((ICmdModule*)mod)->EnterCommand(cmd);
		}
	}
	return bHasCmd;
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
