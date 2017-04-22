#ifndef _configfile_for_ini_kind_config_reading2017_
#define _configfile_for_ini_kind_config_reading2017_

#include <fstream>
#include "../h/common_def.h"

class ConfigFile
{
	string _fn;
	STRMAP _cfg_map;

public:
	ConfigFile();
	ConfigFile(const string& fn);
	virtual ~ConfigFile();

	string GetValue(const string& key){ return _cfg_map[key]; }
	void Add(const string& key, const string& val){ _cfg_map[key] = val; }
	void Del(const string& key);
	
	const STRMAP& GetConfig(){ return _cfg_map; }

	bool Load(const string& fn);
	bool Load(){ return Load(_fn); }

	void Save(const string& fn);
	void Save(){ Save(_fn); }
};

#endif
