#include "jsonfile.h"
#include <iostream>

using namespace jsonfile;

Object::Object(const string& content)
{
}

Object::~Object()
{
}

JSON::JSON(string& buf)
{
}

JSON::JSON(const string& fn)
{
}
	
JSON::~JSON()
{
}

/* 將檔案讀取到字串緩衝 */
bool JSON::Read(const string& fn)
{
	ifstream ifs(fn.c_str());
	if(!ifs){
		cout<<"cannot read "<< fn <<NL;
		return false;
	}

	string line;
	getline(ifs, line); //xml info

	while(getline(ifs, line))
		_buf += line;

	return true;
}