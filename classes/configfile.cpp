#include "configfile.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

ConfigFile::ConfigFile()
{}

ConfigFile::~ConfigFile()
{
	Save();
}

ConfigFile::ConfigFile(const string& fn)
{
	Load(fn);
}

#define SEP '='
bool ConfigFile::Load(const string& fn)
{
	if (!fn.size()) return false;

	cout<<"reading "<<fn<<" ..";

	_fn = fn;
	ifstream ifs(fn.c_str());
	if(!ifs) return false;
	else cout<<" ok\n";
	

	_cfg_map.clear();

	string line;
	int ipos = 0;
	while(getline(ifs, line))
	{
		ipos = 0;
		ipos = line.find(SEP, ipos);
		if (ipos != string::npos)
			_cfg_map[ line.substr(0, ipos) ] = line.substr(ipos+1);
	}

	return true;
}

void ConfigFile::Save(const string& fn)
{
	cout<<"Saving conf:"<<fn<<"..";
	if (!fn.size()) return;
	
	CheckDirExist( fn );

	ofstream ofs(fn.c_str());
	for(STRMAP::iterator i = _cfg_map.begin(); i != _cfg_map.end(); ++i)
		ofs<<i->first<<SEP<<i->second<<'\n';
	cout<<"OK\n";
}

void ConfigFile::Del(const string& key)
{
	STRMAP::iterator itor = _cfg_map.find(key);
	if (itor != _cfg_map.end())
		_cfg_map.erase(itor);
}

void ConfigFile::CheckDirExist(string fn)
{
	size_t pos = fn.rfind('/');
	if ( pos != string::npos)
	{
		mkdir( fn.substr(0, pos).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
	}
}
