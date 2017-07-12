#include "configfile.h"
#include "tool.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

ConfigFile::ConfigFile()
{}

/* 關閉時儲存檔案 */
ConfigFile::~ConfigFile()
{
	Save();
}

/* 建構時載入檔案 */
ConfigFile::ConfigFile(const string& fn)
:_fn(fn)
{
	Load(fn);
}

/* 載入並解析檔案 */
#define SEP '='
bool ConfigFile::Load(const string& fn)
{
	if (!fn.size()) return false;
	
	CheckFileExist(fn);

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

/* 指定檔名存檔 */
void ConfigFile::Save(const string& fn)
{
	cout<<"Saving conf:"<<fn<<"..";
	if (!fn.size()) return;
	
	CheckDirExist( fn );

	ofstream ofs(fn.c_str());
	for(STRMAP::iterator i = _cfg_map.begin(); i != _cfg_map.end(); ++i)
		ofs<<i->first<<SEP<<i->second<<'\n';
	cout<<"OK\n";
}

/* 刪除某一個key-val值 */
void ConfigFile::Del(const string& key)
{
	STRMAP::iterator itor = _cfg_map.find(key);
	if (itor != _cfg_map.end())
		_cfg_map.erase(itor);
}
