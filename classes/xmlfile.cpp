#include "xmlfile.h"
#include <algorithm>
#include <iostream>

using namespace xmlfile;


XMLNode::XMLNode(const string& tag, size_t depth)
:_depth(depth)
{
	_ParseTag(tag);
}

XMLNode::XMLNode(size_t depth)
:_depth(depth)
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

		if (!_tag.size())
			_tag = tok;
		else if (tok.size())
		{
			size_t vpos = tok.find(TOK, 0);
			if (vpos != string::npos)
				_attributes[tok.substr(0, vpos)] = tok.substr(vpos + TOK.size());
		}
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

/* 印出節點資訊 */
void XMLNode::ShowTree()
{
	cout<<_tag<<":("<<_childs.size()<<","<<_attributes.size()<<")"<<NL;
	for( list<XMLNode*>::iterator i = _childs.begin(); i != _childs.end(); ++i)
		(*i)->ShowTree();
}

string XMLNode::AsString(bool asDoc)
{
	string ret;

	if (asDoc)
		for(size_t i = 0; i<_depth; ++i) ret += "\t";
	ret += LAB;
	ret += _tag;

	for (STRMAP::iterator i=_attributes.begin(); i!= _attributes.end(); ++i)
		ret += SEP + i->first + "=" + i->second;
	ret += RAB + (asDoc?NL:"");

	for( list<XMLNode*>::iterator i = _childs.begin(); i != _childs.end(); ++i)
		ret += (*i)->AsString(asDoc);

	if (asDoc)
		for(size_t i = 0; i<_depth; ++i) ret += "\t";
	ret += ELAB + _tag + RAB + (asDoc?NL:"");
	return ret;
}

/* ＝＝＝XML Tree 類別=== */
/* 直接從buf字串建立xml tree */
XMLTree::XMLTree(string& buf)
:StringParser(buf), _root("root")
{
	_DoParse(&_root);
}

/* 讀取並解析xml文件建立xml tree */
XMLTree::XMLTree(const string& fn)
:_savefn(fn), _root("root")
{
	Read(fn);

	int cpos = 0;
	_DoParse(&_root);
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
		cout<<"cannot read "<< fn <<NL;
		return false;
	}

	string line;
	getline(ifs, line); //xml info

	while(getline(ifs, line))
		_buf += line;

	return true;
}

bool XMLTree::Save(const string& fn)
{
	ofstream ofs(fn.c_str());
	if(!ofs){
		cout<<"cannot open "<< fn <<NL;
		return false;
	}
	ofs << _root.AsString(true);
	return true;
}

/* 解析xml內文,搜尋sibling及child. */
XMLNode* XMLTree::_DoParse(XMLNode* parent)
{
	string tag;
	size_t nxpos = 0;
	size_t ndepth = parent->GetDepth() + 1;
	while(nxpos != string::npos) // search sibling
	{
		if (CheckSpecialTag()) continue;

		if (string::npos != (nxpos = _EndOfNode())) // find ENDTAG
		{
			parent->SetContent(_buf.substr(_cpos, nxpos - _cpos));
			return NULL;  //parent's ENDTAG
		}

		if (string::npos != (nxpos = FindNextEmbrace(LAB, ERAB, tag, true))) // find SNGTAG
		{
			parent->AddChild(new XMLNode(tag, ndepth));
		}
		else if (string::npos != (nxpos = FindNextEmbrace(LAB, RAB, tag, true))) // find BEGTAG
		{
			if (0 == tag.compare(0, LCMT.size(), LCMT)) continue; // it's a comment tag

			XMLNode* node = new XMLNode(tag, ndepth);
			parent->AddChild(node);
			_DoParse(node);
			nxpos = FindNextEmbrace(ELAB, RAB, tag, true); // skip ENDTAG
		}
	};
	return NULL;
}

/* 往後搜尋結束tag */
size_t XMLTree::_EndOfNode()
{
	for (size_t i = _cpos; i<_buf.size(); ++i)
	{
		if (0==_buf.compare(i, ELAB.size(), ELAB))
			return i;
		if (0==_buf.compare(i, LAB.size(), LAB))
			return string::npos;
	}
	return _buf.size() - 1;
}
