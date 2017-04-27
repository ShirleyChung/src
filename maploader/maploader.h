#ifndef _map_loader_for_loading_map_data_to_mud__201704
#define _map_loader_for_loading_map_data_to_mud__201704

#include "../classes/funcdisp.hpp"
#include "../classes/singleton.hpp"
#include "../h/mapdata.h"

class MapLoader: public FuncDisp<MapLoader>
{
	string _working_dir;
public:
	MapLoader();
	virtual ~MapLoader();
	
	virtual string GetModuleDesc(){ return "Map Loader v0.0.0.1";}
};

#endif