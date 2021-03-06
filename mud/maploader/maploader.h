#ifndef _map_loader_for_loading_map_data_to_mud__201704
#define _map_loader_for_loading_map_data_to_mud__201704

#include "funcdisp.hpp"
#include "singleton.hpp"
#include "mapdata.h"
#include "xmlfile.h"

using namespace xmlfile;

class MapLoader: public FuncDisp<MapLoader>
{
	string _working_dir;

	void LoadMap(STRARR& cmd);
	void SetWordDir(STRARR& cmd);
	void LoadXML(STRARR& cmd);
	
	map<string, XMLTree> _world;

public:
	MapLoader();
	virtual ~MapLoader();

	virtual string GetModuleDesc(){ return "Map Loader v0.0.0.1";}

};

#endif