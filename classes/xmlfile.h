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
const string LCMT= "!--";
const string RCMT= "-->";
const string SEP=" ";
const string TOK="=";
const string ABS="</>";
const string NL="\n";

string GetToken(const string& str, const string& SEP, size_t spos, size_t epos);

class XMLNode{
protected:
	STRMAP _attributes;
	list<XMLNode*> _childs;

	string _tag, _content;
	size_t _depth;

	void _ParseTag(const string& tagcontent);

public:
	XMLNode(size_t depth = 0);
	XMLNode(const string& tag, size_t depth = 0);
	~XMLNode();

	string AsString(bool asDoc = false);

	void AddChild(XMLNode* node){ _childs.push_back(node); }
	void delChild();
	void ShowTree();

	void SetContent(const string& ct){ _content = ct; }
	void SetTag(const string& tag){ _tag = tag; }
	const string& GetTag(){ return _tag; }
	size_t GetDepth(){ return _depth; }
	void SetDepth(size_t d){ _depth = d; }
};

class XMLTree: private StringParser{
protected:
	string _savefn;

	XMLNode _root;
	XMLNode* _DoParse(XMLNode* parent);
	size_t _EndOfNode();

	virtual bool CheckSpecialTag(){ return false; }

public:
	XMLTree(string& buf);
	XMLTree(const string& fn);
	~XMLTree();

	bool Read(const string& fn);
	bool Save(const string& fn);
	
	void ShowTree(){ _root.ShowTree(); }
	string AsString(){ return _root.AsString(); }
	string AsDocument(){ return _root.AsString(true); }	
};

};//namespace

#endif