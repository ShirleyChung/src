#include "tcpclient.h"
#include <iostream>
#include <arpa/inet.h>
#include <memory.h>

TCPClient::TCPClient()
{}

TCPClient::~TCPClient()
{
	close(_clisck);
}

bool TCPClient::Connect(string ip, int port)
{
	_clisck = socket(AF_INET, SOCK_STREAM, 0);
	if (_clisck<0){ cout<<"socket init err!\n"; return false;}
	in_addr ipv4addr;
	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr.s_addr);
	serv_addr.sin_port = htons(port);
	if ( 0 > connect(_clisck, (sockaddr*)&serv_addr, sizeof(serv_addr)) )
	{
		cout<<" connect error!\n";
		return false;
	}
	cout << ip <<" connect ok.\n";

	return true;
}

bool TCPClient::Send(string msg)
{
	if ( 0 > write(_clisck, msg.c_str(), msg.size()) )
	{	
		cout<<" write to "<<_clisck<<" failed\n";
		return false;
	}
	else
	{
		char buf[256];
		memset(buf, 0, 256);
		read(_clisck, buf, 255);
		cout<<buf<<"\n";
		return true;
	}
}
