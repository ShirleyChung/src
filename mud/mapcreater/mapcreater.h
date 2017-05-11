#ifndef _map_Createer_for_Create_map_and_area_and_items_to_mud_data_201704
#define _map_Createer_for_Create_map_and_area_and_items_to_mud_data_201704

#include "funcdisp.hpp"
#include "singleton.hpp"
#include "mapdata.h"

class MapCreater: public FuncDisp<MapCreater>
{
	string _working_dir;

	void NewMap(STRARR& cmd);
	void NewArea(STRARR& cmd);

	void ModifyMap(STRARR& cmd);
	void ModifyArea(STRARR& cmd);

	void DeleteMap(STRARR& cmd);
	void DeleteArea(STRARR& cmd);

	bool CreateFile(const string& fn);

	void SetWordDir(STRARR& cmd);

public:
	MapCreater();
	virtual ~MapCreater();

	virtual string GetModuleDesc(){ return "Map Creater v0.0.0.1";}
};

#endif