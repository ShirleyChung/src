#include "mapcreater.h"
#include "tool.h"
#include "configfile.h"

extern "C" IModule* GetModule()
{
	return Singleton<MapCreater>::GetInstance();
}

MapCreater::MapCreater()
:_working_dir("maps")
{
	_name = "mapcreater";
	CheckDirExist(_working_dir);

	AddFunc("newmap", &MapCreater::NewMap);
	AddFunc("newarea", &MapCreater::NewArea);
	AddFunc("mfmap", &MapCreater::ModifyMap);
	AddFunc("mfarea", &MapCreater::ModifyArea);
	AddFunc("delmap", &MapCreater::DeleteMap);
	AddFunc("delarea", &MapCreater::DeleteArea);
	AddFunc("setwkdir", &MapCreater::SetWordDir);
}

MapCreater::~MapCreater()
{

}

void MapCreater::SetWordDir(STRARR& cmd)
{
	if ( !cmd.size() )
		cout<<"please specify working dir: setwkdir [working dir]\n";
	else
	{
		cout<<"previous working dir:"<< _working_dir;
		_working_dir = cmd[0];
		cout<<"\nnew working dir:"<< _working_dir<<"\n";
	}
}

void MapCreater::NewMap(STRARR& cmd)
{
	if (cmd.size()>0)
	{
		CheckDirExist(cmd[0]);
		string mdfn = _working_dir + "/" + cmd[0] + MAPDATA;
		ConfigFile conf(mdfn);
		conf.Add("name", cmd[0]);
		if (cmd.size()>1)
			conf.Add("desc", cmd[1]);
		cout<<"Map ["<<cmd[0]<<"] created\n";
	}
	else
		cout<<"newmap (mapname) [desc]\n";
}

void MapCreater::NewArea(STRARR& cmd)
{
	if (cmd.size()>1)
	{
		if(!CheckDirExist)
			NewMap(STRARR(cmd.begin(), cmd.begin()+1));
		string adfn = _working_dir + "/" + cmd[0] + "/" + cmd[1] + AREADATA;
		CheckFileExist(adfn);
		cout<<"Area ["<<cmd[1]<<"] created in ["<<cmd[0]<<"]\n";
	}
	else
		cout<<"newarea (mapname) (areaname)\n";
}

void MapCreater::ModifyMap(STRARR& cmd)
{
	cout<<"not impl.\n";
}

void MapCreater::ModifyArea(STRARR& cmd)
{
	cout<<"not impl.\n";
}

void MapCreater::DeleteMap(STRARR& cmd)
{
	cout<<"not impl.\n";
}

void MapCreater::DeleteArea(STRARR& cmd)
{
}

bool MapCreater::CreateFile(const string& fn)
{
	return false;
}
