#ifndef _xml_file_parse_xml_load_and_save_and_modify_201705_sly_
#define _xml_file_parse_xml_load_and_save_and_modify_201705_sly_

#include <fstream>
#include <map>
#include <list>
#include "stringparser.h"

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
const string ABS="</>";

string GetToken(const string& str, const string& SEP, size_t spos, size_t epos);

class XMLNode{
protected:
	STRMAP _attributes;
	list<XMLNode*> _childs;

	string _tag, _content;

	void _ParseTag(const string& tagcontent);

public:
	XMLNode();
	XMLNode(const string& tag);
	~XMLNode();

	void AddChild(XMLNode* node){ _childs.push_back(node); }
	void delChild();
	void ShowTree();

	void SetContent(const string& ct){ _content = ct; }
	void SetTag(const string& tag){ _tag = tag; }
	const string& GetTag(){ return _tag; }
};

class XMLTree: private StringParser{
protected:
	string _savefn;

	XMLNode _root;
	XMLNode* _DoParse(XMLNode* parent);
	size_t _EndOfNode();
	
public:
	XMLTree(string& buf);
	XMLTree(const string& fn);
	~XMLTree();

	bool Read(const string& fn);
	bool Save();
	void ShowTree();
};

};//namespace

#endif