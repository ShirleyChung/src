#ifndef _member_func_dispatcher_map_2017
#define _member_func_dispatcher_map_2017

#include "../h/icmdmodule.h"
#include "loader.h"

template<class T>
class FuncDisp : public ICmdModule
{
protected:
	typedef void(T::*funcptr)(STRARR&);
	typedef map<string, funcptr> FUNCMAP;
	
	FUNCMAP _func_map;
	
	void AddFunc(const string& key, funcptr func){
		_func_map[key] = func;
	}
	
	/* 將指令傳給每一個有支援icmdmodule的模組 */
	virtual bool EnterCommandToModule(STRARR& cmd)
	{
		if (!_ldr) return false;
		bool bHasCmd = false;

		STRARR arr = _ldr->GetModuleList();
		for( STRARR::const_iterator i = arr.begin(); i != arr.end(); ++i )
		{
			IModule* mod = _ldr->GetModule(*i);
			if (mod->GetSupportedInterfaceType() & I_COMMAND)
			{
				bHasCmd |= ((ICmdModule*)mod)->EnterCommand(cmd);
			}
		}
		return bHasCmd;
	}
	
	/* 取得此模組支援的指令字串陣列 */
	vector<string> GetCommands()
	{
		vector<string> list;
		for( typename FUNCMAP::iterator i = _func_map.begin(); i != _func_map.end(); ++i )
			list.push_back(i->first);
		return list;
	}

	/* 印出模組支援的指令 */
	virtual void ShowSupportedCmds()
	{
		cout<<_name<<" command:\n";

		PrintCmds(GetCommands());
	}
	
	void PrintCmds(STRARR& cmds)
	{
		for( STRARR::const_iterator c = cmds.begin(); c!=cmds.end(); ++c )
			cout<<'\t'<<*c<<'\n';
	}
	
	Loader* _ldr;

public:

	/* 尋找對應的指令, 並執行函式 */
	virtual bool EnterCommand(STRARR& cmd)
	{
		if (cmd.size())
		{
			typename FUNCMAP::iterator i = _func_map.find(cmd[0]);
			if (i == _func_map.end())
			{
				if (!EnterCommandToModule(cmd))
					ShowSupportedCmds();
				return false;
			}
			else
				if (i->second) (((T*)this)->*(i->second))( vector<string>( cmd.begin()+1, cmd.end() )  );
			return true;
		}
		return false;
	}
	
	FuncDisp(Loader* ldr = NULL):_ldr(ldr){}
};

#endif
