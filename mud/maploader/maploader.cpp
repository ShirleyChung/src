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
		_world.insert( std::pair<string, XMLTree>(cmd[0], XMLTree(mappath)) );
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

void MapLoader::LoadXML(STRARR& cmd)
{
	if (cmd.size())
	{
		XMLTree xtree(cmd[0]);
		xtree.ShowTree();
	}
	else
		cout << "please enter xml file name\n";
}