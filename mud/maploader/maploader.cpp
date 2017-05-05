#include "maploader.h"
#include "tool.h"

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

	}
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

