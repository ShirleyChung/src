#include "tool.h"

#define SEP ' '
vector<string> Tokenize(const string& line)
{
	vector<string> list;
	size_t pos = 0, curpos = 0;
	while( curpos != string::npos)
	{
		curpos = line.find(SEP, pos);
		string tok = (curpos == string::npos)? line.substr(pos): line.substr(pos, curpos - pos);

		if (tok.size())
			list.push_back( tok );
		
		pos = curpos + 1;
	}
	return list;	
}

string Tokencombine(const vector<string>& arr)
{
	string line;
	for( vector<string>::const_iterator i = arr.begin(); i != arr.end(); ++i )
		line += *i + SEP;
	return line;
}
