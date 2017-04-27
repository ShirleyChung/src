#include "mapcreater.h"
#include "../classes/tool.h"

extern "C" IModule* GetModule()
{
	return Singleton<MapCreater>::GetInstance();
}

MapCreater::MapCreater()
:_working_dir("maps")
{
	_name = "mapcreater";
	CheckDirExist(_working_dir);
}

MapCreater::~MapCreater()
{

}
