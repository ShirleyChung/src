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
	list<XMLNode*> _childs;
	string _content;

	void _ParseTag(const string& tagcontent);

public:
	XMLNode();
	XMLNode(const string& tag);
	~XMLNode();
	
	bool hasChild(){ return false; }
	void AddChild(XMLNode* node){ _childs.push_back(node); }
	
};

class XMLTree{
	string _savefn;
	
	string& _xmlbuf;
	string _tmpxmlbuf;
	string _stack;
	
	XMLNode _root;
	XMLNode* _DoParse(XMLNode* parent, const string& buf, int& cpos);

	XMLNode* _FindTag(const string& buf, int& cpos);
	
	void _destruct(XMLNode*);
public:
	XMLTree(string& buf);
	XMLTree(const string& fn);
	~XMLTree();
	
	bool Read(const string& fn);
	bool Save();
};

};

#endif