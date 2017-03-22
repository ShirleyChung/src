#ifndef _loader_for_modules_funcationlities_2017_03
#define _loader_for_modules_funcationlities_2017_03

#include <string>
#include <dlfcn.h>
#include <iostream>

#include "../h/common_def.h"
#include "../h/imodule.h"

typedef IModule* (*GetModuleProc)();
typedef map<string, IModule*> MODMAP;

class Loader
{
	void* _handle;
	IModule* _module;
	
	MODMAP _mod_map;
public:
	Loader();
	Loader(const string&);
	virtual ~Loader();

	IModule* Load(const string& file);
	void Load(const STRMAP& cfg);

	IModule* GetModule(const string& modname){ return _mod_map[modname]; }
	
	vector<string> GetModuleList();
};

#endif
