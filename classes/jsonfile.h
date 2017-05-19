#ifndef _json_parser_and_build_key_wvlue_truee_2017_05_
#define _json_parser_and_build_key_wvlue_truee_2017_05_

#include <fstream>
#include <map>
#include <list>
#include "stringparser.h"

using namespace std;


namespace jsonfile{
const string LPP = "{";
const string RPP = "}";
const string LBP = "[";
const string RBP = "]";
const string NL  = "\n";


class Object{
protected:
typedef map<string, Object> ITEM;

	list<Object*> _items;
public:
	Object(const string& content);
	virtual ~Object();
};

class JSON: private StringParser
{
protected:
	void _DoParse(Object* parent);
public:

	JSON(string& buf);
	JSON(const string& fn);
	
	virtual ~JSON();
	
	bool Read(const string& fn);
	bool Save();
	void ShowTree();
};

};

#endif
