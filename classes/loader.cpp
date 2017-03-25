#include "loader.h"

Loader::Loader()
:_handle(NULL), _module(NULL)
{}

Loader::Loader(const string& fn)
:_conf(fn)
{
	Load(_conf.GetConfig());
}

Loader::~Loader()
{
	_conf.Save();
}

IModule* Loader::Load(const string& fn)
{
	cout << "Loading " << fn << " ...";

	_handle = dlopen(fn.c_str(), RTLD_LAZY);
	if (!_handle)
	{
		cout<<"load "<<fn<<" failed:"<<dlerror()<<"\n";
		return NULL;
	}
	
	cout<<"OK\n";

	GetModuleProc gm = (GetModuleProc)dlsym(_handle, "GetModule");
	if (gm)
		return (*gm)();
	else{
		cout<< "No modules in "<<fn<<'\n';
		return NULL;
	}
}

void Loader::Load(const STRMAP& cfg)
{
	for( STRMAP::const_iterator i = cfg.begin(); i != cfg.end(); ++i)
	{
		IModule* mod = Load(i->second);
		if (mod)
			_mod_map[i->first] = mod;
	}
}

bool Loader::AddMod(const string& name, const string& path)
{
	IModule* mod = Load(path);
	if (mod)
	{
		_mod_map[name] = mod;
		_conf.Add(name, path);
	}
}

vector<string> Loader::GetModuleList()
{
	vector<string> list;
	for(MODMAP::iterator i = _mod_map.begin(); i != _mod_map.end(); ++i)
		list.push_back(i->first);
	return list;
}

