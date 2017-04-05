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
	typedef map<funcptr, string> FUNC2CMD;
	
	FUNCMAP _func_map;
	string _supportCmds;
	
	void AddFunc(const string& key, funcptr func){
		_func_map[key] = func;
	}
	
	/* 搜尋模組中對應的指令並執行 */
	virtual bool EnterCommandToModule(STRARR& cmd)
	{
		_supportCmds = SupportedCmdString(GetCommands());				

		if (!_ldr) return false;

		STRARR arr = _ldr->GetModuleList();
		for( STRARR::const_iterator i = arr.begin(); i != arr.end(); ++i )
		{
			IModule* mod = _ldr->GetModule(*i);
			if (mod->GetSupportedInterfaceType() & I_COMMAND)
			{
				ICmdModule* cmod = (ICmdModule*)mod;
				if ( cmod->EnterCommand(cmd) )
					return true;
				else
					_supportCmds += SupportedCmdString(cmod->GetCommands());				
			}
		}

		return false;
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
	virtual string SupportedCmdString(STRARR& cmds)
	{
		string cmdlist;
		for( STRARR::const_iterator c = cmds.begin(); c!=cmds.end(); ++c )
			cmdlist += '\t' + *c + '\n';
		return cmdlist;
	}	
	
	Loader* _ldr;

public:

	virtual string GetSupportedCmdString(){ return _supportCmds; }

	/* 尋找對應的指令, 並執行函式 */
	virtual bool EnterCommand(STRARR& cmd)
	{
		if (cmd.size())
		{
			typename FUNCMAP::iterator i = _func_map.find(cmd[0]);
			if (i == _func_map.end())
			{
				if (!EnterCommandToModule(cmd))
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
