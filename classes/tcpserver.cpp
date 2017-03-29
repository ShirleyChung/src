#include "tcpserver.h"
#include <iostream>

TCPServer::TCPServer()
{
}

TCPServer::TCPServer(unsigned int port)
:_port(port)
{
}

TCPServer::~TCPServer()
{}

bool TCPServer::Init()
{
	
	memset(&_sckaddr, 0, sizeof(_sckaddr));

	_sckaddr.sin_family = AF_INET;
	_sckaddr.sin_addr.s_addr = INADDR_ANY;
	_sckaddr.sin_port = htons(_port);
	
	_svrsck = socket(AF_INET, SOCK_STREAM, 0);
	if (_svrsck <0)
	{
		cout<<" socket open error!\n";
		return false;
	}
	
	if (0 != bind(_svrsck, (sockaddr*)&_sckaddr, sizeof(_sckaddr)))
	{	
		cout<<"bind "<<_port<<" error.\n";
		return false;
	}
	return true;
}
