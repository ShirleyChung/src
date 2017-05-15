#include "xmlfile.h"
#include <algorithm>

using namespace xmlfile;


string GetToken(const string& str, const string& SEP, size_t spos, size_t epos)
{
		
}

XMLNode::XMLNode(const string& tag)
{
}

XMLNode::XMLNode()
{
}

XMLNode::~XMLNode()
{
}

XMLTree::XMLTree(string& buf)
:_xmlbuf(buf)
{
	_DoParse(_xmlbuf);
}

XMLTree::XMLTree(const string& fn)
:_xmlbuf(_tmpxmlbuf)
,_savefn(fn)
{
	Read(fn);
	_DoParse(_xmlbuf);
}

XMLTree::~XMLTree()
{
}

bool XMLTree::Read(const string& fn)
{
	ifstream ifs(fn.c_str());
	if(!ifs){
		cout<<"cannot read "<< fn <<"\n";
		return false;
	}
	
	string line;
	getline(ifs, line); //xml info
	
	while(getline(ifs, line))
		_xmlbuf += line;
	
	return true;
}

bool XMLTree::_DoParse(string& buf)
{
	size_t doclen = buf.size(), cpos = 0;
	
	XMLNode* next_node = _ParseNextNode(buf, cpos);

	return true;
}

XMLNode* XMLTree::_ParseNextNode(const string& buf, int& pos)
{
	return NULL;
}





