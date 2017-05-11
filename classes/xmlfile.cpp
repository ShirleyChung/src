#include "xmlfile.h"

using namespace xmlfile;

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
}

XMLTree::XMLTree(const string& fn)
:_xmlbuf(_tmpxmlbuf)
{
}
	
XMLTree::~XMLTree()
{
}


