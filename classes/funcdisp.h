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
	
	virtual bool EnterCommandToModule(STRARR& cmd)
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

	virtual void ShowSupportedCmds()
	{
		cout<<"Supported command:\n";
		for( typename FUNCMAP::iterator i = _func_map.begin(); i != _func_map.end(); ++i )
			cout<< '\t' << i->first << '\n';
	}
	
	Loader& _ldr;

public:

	virtual void EnterCommand(STRARR& cmd)
	{
		if (cmd.size())
		{
			typename FUNCMAP::iterator i = _func_map.find(cmd[0]);
			if (i == _func_map.end())
			{
				if (!EnterCommandToModule(cmd))
					ShowSupportedCmds();
			}
			else
				(((T*)this)->*(i->second))( vector<string>( cmd.begin()+1, cmd.end() )  );
		}
	}
	
	FuncDisp(Loader& ldr):_ldr(ldr){}
};

#endif
