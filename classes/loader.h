#ifndef _loader_for_modules_funcationlities_2017_03
#define _loader_for_modules_funcationlities_2017_03

#include <string>
#include <dlfcn.h>

#include "../h/imodule.h"

#include <iostream>

typedef IModule* (*GetModuleProc)();

using namespace std;

class Loader
{
	void* _handle;
	IModule* _module;
public:
	Loader();
	Loader(const string&);
	virtual ~Loader();

	bool Load(const string& file);

	IModule* GetModule(){ return _module; }
};

#endif
