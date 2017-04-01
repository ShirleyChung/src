#include "tool.h"

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

string Tokencombine(const vector<string>& arr, const string& sep)
{
	string line;
	for( vector<string>::const_iterator i = arr.begin(); i != arr.end(); ++i )
		line += *i + sep;
	return line;
}

string Tokencombine(const vector<string>& arr)
{
	return Tokencombine(arr, " ");
}
