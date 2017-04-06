#include "tcpserver.h"
#include <iostream>
#include <memory.h>
#include <arpa/inet.h>

TCPServer::TCPServer()
:_lsnNum(5)
,_bufSz(1024)
,_do_wait(true)
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
	listen(_svrsck, _lsnNum);
	cout<<" listening port:"<<_port<<" ,socket:"<<_svrsck<<"\n";
	sockaddr_in cliaddr;
	socklen_t clilen = sizeof(sockaddr);
	int newsck = accept(_svrsck, (sockaddr*)&cliaddr, &clilen);	
	if (newsck<0) cout<<" accept failed!\n";
	else
		cout<<"Accepted.\n";

	char* buf = new char[_bufSz];
	string msg, ret = "I got it";
	do
	{
		memset(buf, 0, _bufSz);
		int n = read(newsck, buf, _bufSz);
		msg = buf;
		cout<<"msg="<<msg<<", sizeof msg="<<msg.size()<<'\n';
		n = write(newsck, ret.c_str(), ret.size());
	}while( msg != "ok");
	
	close(newsck);
	cout<<" socket "<<newsck<<" closed.\n";

	delete[] buf;
}

void TCPServer::WaitForConnection()
{
	listen(_svrsck, _lsnNum);
	cout<<" listening port:"<<_port<<" ,socket:"<<_svrsck<<"\n";
	sockaddr_in cliaddr;
	socklen_t clilen = sizeof(sockaddr);

	_sckmap.clear();

	while(_do_wait)
	{
		int sck = accept(_svrsck, (sockaddr*)&cliaddr, &clilen);	
		if (sck<0)
			cout<<" accept failed!\n";
		else
		{
			cout<<"Accepted.\n";
			char buf[INET_ADDRSTRLEN];memset(buf, 0, INET_ADDRSTRLEN);
			inet_ntop(AF_INET, &cliaddr.sin_addr, buf, INET_ADDRSTRLEN);
			string cip = buf;
			_sckmap[cip] = sck;
		}
	}
}
