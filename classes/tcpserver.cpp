#include "tcpserver.h"
#include <iostream>
#include <memory.h>

TCPServer::TCPServer()
{
}

TCPServer::~TCPServer()
{
	close(_svrsck);
}

bool TCPServer::Init(int port)
{
	_port = port;
	
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

void TCPServer::Echo()
{
	listen(_svrsck, 5);
	cout<<" listening port:"<<_port<<" ,socket:"<<_svrsck<<"\n";
	sockaddr_in cliaddr;
	socklen_t clilen = sizeof(sockaddr);
	int newsck = accept(_svrsck, (sockaddr*)&cliaddr, &clilen);	
	if (newsck<0) cout<<" accept failed!\n";
	else
		cout<<"Accepted.\n";

	char buf[256];
	string msg, ret = "I got it";
	do
	{
		memset(buf, 0, 256);
		int n = read(newsck, buf, 255);
		msg = buf;
		cout<<msg<<'\n';
		n = write(newsck, ret.c_str(), ret.size());
	}while( msg != "ok");
	
	close(newsck);
	cout<<" socket "<<newsck<<" closed.\n";
}
