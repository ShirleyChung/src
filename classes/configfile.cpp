#include "configfile.h"
#include <iostream>

ConfigFile::ConfigFile()
{}

ConfigFile::~ConfigFile()
{
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

bool ConfigFile::Write(const string& key, const string& val)
{
	return Write(_fn, key, val);
}

bool ConfigFile::Write(const string& fn, const string& key, const string& val)
{
	if (!fn.size()) return false;

	cout<<"Writing "<<fn<<" ..\n";

	ofstream ofs(fn.c_str());
	if (!ofs) return false;

	ofs<<key<<SEP<<val<<'\n';

	return true;
}
