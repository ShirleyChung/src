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
}

MapLoader::~MapLoader()
{

}
