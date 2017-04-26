#include "tool.h"
#include <algorithm>
#include <sys/stat.h>
#include <stdio.h>

vector<string> Tokenize(const string& line, const string& sep)
{
	vector<string> list;
	size_t pos = 0, curpos = 0;
	while( curpos != string::npos)
	{
		curpos = line.find(sep, pos);
		string tok = (curpos == string::npos)? line.substr(pos): line.substr(pos, curpos - pos);

		if (tok.size())
			list.push_back( tok );
		
		pos = curpos + sep.size();
	}
	return list;	
}

vector<string> Tokenize(const string& str)
{
	return Tokenize(str, " ");	
}

string& rtrim(string& s, const string& sep)
{
	if (!s.size()) return s;
	s.erase( s.find_last_not_of(sep)+1 );
	return s;
}

string Tokencombine(const vector<string>& arr, const string& sep)
{
	string line;
	for( vector<string>::const_iterator i = arr.begin(); i != arr.end(); ++i )
		line += *i + sep;
	rtrim(line, sep);
	return line;
}

string Tokencombine(const vector<string>& arr)
{
	return Tokencombine(arr, " ");
}

void CheckDirExist(const string& fn)
{
	size_t pos = fn.rfind('/');
	if ( pos != string::npos)
	{
		mkdir( fn.substr(0, pos).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
	}
}

void CheckFileExist(const string& fn)
{
	FILE* fp = fopen(fn.c_str(), "r");
	if (!fp)
	{	
		fp = fopen(fn.c_str(), "w");
	}
	fclose(fp);
}