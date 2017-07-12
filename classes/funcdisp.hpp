#ifndef _member_func_dispatcher_map_2017
#define _member_func_dispatcher_map_2017

#include "../h/icmdmodule.h"
#include "loader.h"

/* �������O�����J���Ҳ� */
/* ��J���O���Ҳ�: EnterCommandToModule */
/* ���o�Ҳի��O  : GetCommands() */
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
	
	/* �j�M�Ҳդ����������O�ð��� */
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
	
	/* ���o���Ҳդ䴩�����O�r��}�C */
	vector<string> GetCommands()
	{
		vector<string> list;
		for( typename FUNCMAP::iterator i = _func_map.begin(); i != _func_map.end(); ++i )
			list.push_back(i->first);
		return list;
	}

	/* �L�X�Ҳդ䴩�����O */
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

	/* �M����������O, �ð���禡 */
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
