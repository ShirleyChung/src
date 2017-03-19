#ifndef _configfile_for_ini_kind_config_reading2017_
#define _configfile_for_ini_kind_config_reading2017_

#include <fstream>
#include <map>

using namespace std;

typedef map<string,string> STRMAP;

class ConfigFile
{
	string _fn;
	STRMAP _cfg_map;

public:
	ConfigFile();
	ConfigFile(const string& fn);
	virtual ~ConfigFile();

	bool Load(const string& fn);
	bool Write(const string& key, const string& val);
	bool Write(const string& fn, const string& key, const string& val);
};

#endif
