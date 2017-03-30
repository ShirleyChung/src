#include "system.h"
#include "../../classes/tool.h"

System sys;

/* 設定給console的輸入字串回呼函式 */
void CmdHandler(STRARR& cmd)
{
	sys.EnterCommand(cmd);
}

/* 設定給module的輸入字串回呼函式 */
void CallbackHanlder(string cmd)
{
	sys.EnterCommand(Tokenize(cmd));
}

/* System類別的constructor*/
System::System()
:_ldr("./conf/loadmodule.cfg")
,FuncDisp<System>(&_ldr)
{	
	_name = "system";
	
	AddFunc("listmod", &System::ListModule);
	AddFunc("loadmod", &System::LoadModule);
	AddFunc("unloadmod", &System::UnLoadModule);
	AddFunc("setprompt", &System::SetPrompt);
	
	_con.AddCommandHandler(CmdHandler);

	SetModuleOutputCallback(CallbackHanlder);
}

System::~System()
{
}

/* Run: 執行console */
void System::Run()
{
	_con.Prompt();
}

/* System指令功能:列出模組名稱及描述 */
void System::ListModule(STRARR&)
{
	vector<string> modlist = _ldr.GetModuleList();
	for( vector<string>::iterator i = modlist.begin(); i != modlist.end(); ++i)
		cout<<*i<<" = "<<_ldr.GetModule(*i)->GetModuleDesc()<<'\n';
}

/* System指令功能:載入模組 */
void System::LoadModule(STRARR& cmd)
{
	if (cmd.size()>1)
		_ldr.AddMod(cmd[0], cmd[1]);
	else
		cout<<"please specify module name and module path\n";
}

/* System指令功能:卸除模組 */
void System::UnLoadModule(STRARR& cmd)
{
	if (cmd.size()>0)
		_ldr.DelMod(cmd[0]);
	else
		cout<<"please specify module name and module path\n";
}

void System::SetPrompt(STRARR& cmd)
{
	if (cmd.size())
		_con.SetPrompt(cmd[0]);
	else
		cout<<"please enter prompt string\n";
}

/* 設定所有ldr載入的模組的字串回呼函式 */
void System::SetModuleOutputCallback(OutputCallback cb)
{
	vector<string> modlist = _ldr.GetModuleList();
	for( vector<string>::iterator i = modlist.begin(); i != modlist.end(); ++i)
	{
		IModule* mod = _ldr.GetModule(*i);
		if (mod->GetSupportedInterfaceType() & I_COMMAND)
			((ICmdModule*)mod)->SetOutputCallback(cb);
	}
}

/* 程式進入點 */
int main(int argc, char* argv[])
{
	std::cout<<"system\n";
	
	sys.Run();

	return 0;
}
