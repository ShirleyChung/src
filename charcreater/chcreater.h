#ifndef _create_characters_such_as_a_user_char_or_npc_event_mob_to_mud_data_201704
#define _create_characters_such_as_a_user_char_or_npc_event_mob_to_mud_data_201704

#include "funcdisp.hpp"
#include "singleton.hpp"
#include "mapdata.h"

class CharaterCreater: public FuncDisp<CharaterCreater>
{
	string _working_dir;
	
	void NewCharacter(STRARR& cmd);
	void ModifyCharacter(STRARR& cmd);	
	void DeleteCharacter(STRARR& cmd);
	
	bool CreateFile(const string& fn);
	
public:
	CharaterCreater();
	virtual ~CharaterCreater();
	
	virtual string GetModuleDesc(){ return "Charater Creater v0.0.0.1";}
};

#endif