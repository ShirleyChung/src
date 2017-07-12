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
}

IModule* Loader::Load(const string& fn)
{
	cout << "Loading " << fn << " ...";

#ifdef posix
	_handle = dlopen(fn.c_str(), RTLD_LAZY);
#else
	_handle = LoadLibrary(fn.c_str());	
#endif
	if (!_handle)
	{
		cout<<"load "<<fn<<" failed:\n";
		return NULL;
	}
	
	cout<<"OK\n";

#ifdef posix
	GetModuleProc gm = (GetModuleProc)dlsym(_handle, "GetModule");
#else
	GetModuleProc gm = (GetModuleProc)GetProcAddress((HMODULE)_handle, "GetModule");
#endif
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
		return true;
	}
	else
		return false;
}

bool Loader::AddMod(const string& path)
{
	IModule* mod = Load(path);
	if (mod)
	{
		string name = mod->GetName();
		_mod_map[name] = mod;
		_conf.Add(name, path);
		return true;
	}
	else
		return false;
}

bool Loader::DelMod(const string& name)
{
	MODMAP::iterator itor = _mod_map.find(name);
	if ( itor != _mod_map.end() )
	{
		delete itor->second;
		_mod_map.erase(itor);
		_conf.Del(name);
		return true;
	}
	else
		return false;
}

vector<string> Loader::GetModuleList()
{
	vector<string> list;
	for(MODMAP::iterator i = _mod_map.begin(); i != _mod_map.end(); ++i)
		list.push_back(i->first);
	return list;
}

