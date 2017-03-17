#include "loader.h"

Loader::Loader()
:_handle(NULL), _module(NULL)
{}

Loader::Loader(const string& fn)
{
	Load(fn);
}

Loader::~Loader()
{}

bool Loader::Load(const string& fn)
{
	cout << "Loading " << fn << " ...\n";

	_handle = dlopen(fn.c_str(), RTLD_LAZY);
	if (!_handle)
	{
		cout<<"load "<<fn<<" failed:"<<dlerror()<<"\n";
		return false;
	}

	cout << fn << " Get OK. Retrieving Module...\n";

	GetModuleProc gm = (GetModuleProc)dlsym(_handle, "GetModule");
	if (gm)
		_module = (*gm)();
	else
		return false;

	cout << "Module Get OK!\n";

	return true;
}
