#include "xmlfile.h"
#include <algorithm>
#include <iostream>

using namespace xmlfile;


string GetToken(const string& str, const string& SEP, size_t spos, size_t epos)
{
		
}

XMLNode::XMLNode(const string& tag)
{
	_ParseTag(tag);
}

XMLNode::XMLNode()
{
}

XMLNode::~XMLNode()
{
}

/* 解析Tag的內容 */
void XMLNode::_ParseTag(const string& tc)
{
		size_t pos = 0, curpos = 0;
		while( curpos != string::npos)
		{
			curpos = tc.find(SEP, pos);
			string tok = (curpos == string::npos)? tc.substr(pos): tc.substr(pos, curpos - pos);
	
//			if (tok.size())
//				list.push_back( tok );
			
			pos = curpos + SEP.size();
		}	
}


/* ＝＝＝XML Tree 類別=== */
/* 直接從buf字串建立xml tree */
XMLTree::XMLTree(string& buf)
:_xmlbuf(buf)
{
	int cpos = 0;
	_DoParse(&_root, _xmlbuf, cpos);
}

/* 讀取並解析xml文件建立xml tree */
XMLTree::XMLTree(const string& fn)
:_xmlbuf(_tmpxmlbuf)
,_savefn(fn)
{
	Read(fn);
	
	int cpos = 0;
	_DoParse(&_root, _xmlbuf, cpos);
}

XMLTree::~XMLTree()
{
	_destruct(&_root);
}

void XMLTree::_destruct(XMLNode* node)
{
	//iterate to delete tree
}

/* 將檔案讀取到字串緩衝 */
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

/* 解析buf字串 */
XMLNode* XMLTree::_DoParse(XMLNode* parent, const string& buf, int& cpos)
{
	XMLNode* node = NULL;
	while(cpos != string::npos)
	{
		node = _FindTag(buf, cpos);
		if (node)
			if (node->hasChild())
			{
					_DoParse(node, buf, cpos);
					parent->AddChild(node);
			}
		else
			break;
	};

	return node;;
}

/* 從buf裡依序找出tag */
XMLNode* XMLTree::_FindTag(const string& buf, int& cpos)
{	
	cpos = buf.find(LAB, cpos);
	if (cpos != string::npos) // found '<'
	{
		size_t epos = buf.find_first_of(RAB, cpos); // found '/ or />'
		if (epos != string::npos)
		{
			XMLNode* node = new XMLNode( buf.substr( cpos + 1, epos - cpos ) );
			return node;
		}
	}
	return NULL;
}






