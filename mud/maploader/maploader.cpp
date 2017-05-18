#include "maploader.h"
#include "tool.h"
#include "configfile.h"
#include "xmlfile.h"

extern "C" IModule* GetModule()
{
	return Singleton<MapLoader>::GetInstance();
}

MapLoader::MapLoader()
:_working_dir("maps")
{
	_name = "maploader";
	CheckDirExist(_working_dir);

	AddFunc("ldmap", &MapLoader::LoadMap);
	AddFunc("setwkdir", &MapLoader::SetWordDir);
	AddFunc("ldxml", &MapLoader::LoadXML);
		
}

MapLoader::~MapLoader()
{

}

void MapLoader::LoadMap(STRARR& cmd)
{
	if ( !cmd.size() )
		cout<<"please specify map name: ldmap [mapname]\n";
	else
	{
		string mappath = _working_dir + "/" + cmd[0];
		ConfigFile mapdata(mappath + MAPDATA);
		for( STRMAP::const_iterator i = mapdata.GetConfig().begin(); i != mapdata.GetConfig().end(); ++i )
			if (i->first != "name" && i->first != "desc")
				_world[i->second] = LoadArea( mappath + "/" + i->second);
	}
}

Area MapLoader::LoadArea(string areapath)
{
	ConfigFile areadata(areapath + AREADATA);
	Area area;
	area.name = areadata.GetValue("name");
	area.desc = areadata.GetValue("desc");
	return area;
}


void MapLoader::SetWordDir(STRARR& cmd)
{
	if ( !cmd.size() )
		cout<<"please specify working dir: setwkdir [working dir]\n";
	else
	{
		cout<<"previous working dir:"<< _working_dir;
		_working_dir = cmd[0];
		cout<<"\nnew working dir:"<< _working_dir <<"\n";
	}
}

void MapLoader::LoadXML(STRARR& cmd)
{
	xmlfile::XMLTree xtree(cmd[0]);
	xtree.ShowTree();
}

