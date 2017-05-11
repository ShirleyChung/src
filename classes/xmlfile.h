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
const string LCMT= "<!==";
const string RCMT= "-->";

class XMLNode{
	STRMAP _attributes;
	list<XMLNode> _firstChild;
	list<XMLNode> _firstSibling;
	string _content;
public:
	XMLNode();
	XMLNode(const string& tag);
	~XMLNode();
	
};

class XMLTree{
	string _savefn;
	
	string& _xmlbuf;
	string _tmpxmlbuf;
	XMLNode _root;
public:
	XMLTree(string& buf);
	XMLTree(const string& fn);
	~XMLTree();
};

};

#endif