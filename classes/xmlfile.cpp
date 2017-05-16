#include "xmlfile.h"
#include <algorithm>
#include <iostream>

using namespace xmlfile;


string GetToken(const string& str, const string& SEP, size_t spos, size_t epos)
{

}

XMLNode::XMLNode(const string& tag)
:hasChild(false), hasContent(false)
{
	_ParseTag(tag);
}

XMLNode::XMLNode()
:hasChild(false), hasContent(false)
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

/* 清除所有子節點 */
void XMLNode::delChild()
{
	for( list<XMLNode*>::iterator i = _childs.begin(); i != _childs.end(); ++i)
	{
		(*i)->delChild();
		delete *i;
	}
	_childs.clear();
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
	_root.delChild();
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
	size_t epos;
	while(cpos != string::npos)
	{
		node = _FindTag(buf, cpos);
		if (node)
			if (node->hasChild)
			{
				_DoParse(node, buf, cpos);
				parent->AddChild(node);
			}
			else if (string::npos != (epos = _FindEndTag(buf, cpos)))
			{
				node->content = buf.substr(cpos, epos - cpos);
				cpos = epos;
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
		size_t epos = buf.find(ERAB, cpos); // find '/>'
		if (epos != string::npos) //no child, no content
		{
			XMLNode* node = new XMLNode( buf.substr( cpos + 1, epos - cpos ) );
			cpos = epos + sizeof(ERAB);
			return node;
		}
		else if ( string::npos != (epos = buf.find(RAB, cpos)) ) // find '>'
		{
			XMLNode* node = new XMLNode( buf.substr( cpos + 1, epos - cpos ) );
			node->hasContent = (buf.find(ELAB, epos + 1) != string::npos);
			cpos = epos + sizeof(RAB);
			if (node->hasContent) return node;

			node->hasChild = (buf.find(LAB, epos + 1) != string::npos);
			return node;
		}
	}
	return NULL;
}

/* 找出結尾的tag */
size_t XMLTree::_FindEndTag(const string& buf, int& cpos)
{
	size_t epos = buf.find(ELAB, cpos);
	return epos;
}







