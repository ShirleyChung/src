#ifndef _map_Createer_for_Create_map_and_area_and_items_to_mud_data_201704
#define _map_Createer_for_Create_map_and_area_and_items_to_mud_data_201704

#include "../classes/funcdisp.hpp"
#include "../classes/singleton.hpp"
#include "../h/mapdata.h"

class MapCreater: public FuncDisp<MapCreater>
{
	string _working_dir;
public:
	MapCreater();
	virtual ~MapCreater();
	
	virtual string GetModuleDesc(){ return "Map Creater v0.0.0.1";}
};

#endif