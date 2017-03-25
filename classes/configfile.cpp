#include "configfile.h"
#include <iostream>

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

	ofstream ofs(fn.c_str());
	for(STRMAP::iterator i = _cfg_map.begin(); i != _cfg_map.end(); ++i)
		ofs<<i->first<<SEP<<i->second<<'\n';
	cout<<"OK\n";
}
