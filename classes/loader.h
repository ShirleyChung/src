#ifndef _loader_for_modules_funcationlities_2017_03
#define _loader_for_modules_funcationlities_2017_03

#include <string>
#include <dlfcn.h>
#include <iostream>

#include "../h/common_def.h"
#include "../h/imodule.h"
#include "configfile.h"

typedef IModule* (*GetModuleProc)();
typedef map<string, IModule*> MODMAP;

class Loader
{
	void* _handle;
	IModule* _module;
	
	MODMAP _mod_map;

	ConfigFile _conf;
public:
	Loader();
	Loader(const string&);
	virtual ~Loader();

	IModule* Load(const string& file);
	void Load(const STRMAP& cfg);
	bool AddMod(const string& name, const string& path);
	bool AddMod(const string& paht);
	bool DelMod(const string& name);

	IModule* GetModule(const string& modname){ return _mod_map[modname]; }
	
	vector<string> GetModuleList();
};

#endif
