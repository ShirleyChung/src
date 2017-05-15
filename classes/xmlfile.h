#ifndef _xml_file_parse_xml_load_and_save_and_modify_201705_sly_
#define _xml_file_parse_xml_load_and_save_and_modify_201705_sly_

#include <string>
#include <fstream>
#include <map>
#include <list>

using namespace std;

namespace xmlfile
{
typedef map<string, string> STRMAP;
const string LAB = "<";
const string RAB = ">";
const string RABE = "/>";
const string LCMT= "<!==";
const string RCMT= "-->";
const string SEP=" ";

string GetToken(const string& str, const string& SEP, size_t spos, size_t epos);

class XMLNode{
	STRMAP _attributes;
	list<XMLNode*> _firstChild;
	string _content;

	XMLNode* _curNode;
public:
	XMLNode();
	XMLNode(const string& tag);
	~XMLNode();
	
};

class XMLTree{
	string _savefn;
	
	string& _xmlbuf;
	string _tmpxmlbuf;
	string _stack;
	
	XMLNode _root;
	bool _DoParse(string& buf);

	XMLNode* _ParseNextNode(const string& buf, int& cpos);

public:
	XMLTree(string& buf);
	XMLTree(const string& fn);
	~XMLTree();
	
	bool Read(const string& fn);
	bool Save();
};

};

#endif