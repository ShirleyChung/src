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
const string ELAB = "</";
const string ERAB = "/>";
const string LCMT= "<!--";
const string RCMT= "-->";
const string SEP=" ";
const string TOK="=";

string GetToken(const string& str, const string& SEP, size_t spos, size_t epos);

class XMLNode{
	STRMAP _attributes;
	list<XMLNode*> _childs;

	void _ParseTag(const string& tagcontent);

public:
	XMLNode();
	XMLNode(const string& tag);
	~XMLNode();

	void AddChild(XMLNode* node){ _childs.push_back(node); }

	void delChild();

	bool hasChild, hasContent;
	string tag, content;
};

class XMLTree{
	string _savefn;

	string& _xmlbuf;
	string _tmpxmlbuf;
	string _stack;

	XMLNode _root;
	XMLNode* _DoParse(XMLNode* parent, const string& buf, int& cpos);

	XMLNode* _FindTag(const string& buf, int& cpos);
	size_t _FindEndTag(const string& buf, int& cpos, const string& beginTag);
public:
	XMLTree(string& buf);
	XMLTree(const string& fn);
	~XMLTree();

	bool Read(const string& fn);
	bool Save();
};

};

#endif