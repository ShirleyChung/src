#include "tcpclient.h"
#include <iostream>
#include <arpa/inet.h>
#include <memory.h>

TCPClient::TCPClient()
:_bufSz(1024)
{}

TCPClient::~TCPClient()
{
	CloseAll();
}

void TCPClient::CloseAll()
{
	for( SCKMAP::iterator i = _sckmap.begin(); i != _sckmap.end(); ++i )
		close(i->second);
	_sckmap.clear();
}

bool TCPClient::Connect(string ip, int port)
{
	int sck = socket(AF_INET, SOCK_STREAM, 0);
	_sckmap[ip] = sck;

	if (sck<0){ cout<<"socket init err!\n"; return false;}
	in_addr ipv4addr;
	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr.s_addr);
	serv_addr.sin_port = htons(port);
	if ( 0 > connect(sck, (sockaddr*)&serv_addr, sizeof(serv_addr)) )
	{
		cout<<" connect error!\n";
		return false;
	}
	cout << ip <<" connect ok.\n";

	return true;
}

bool TCPClient::Send(string msg)
{
	SCKMAP::iterator i = _sckmap.begin();
	if (i == _sckmap.end()) return false;

	if ( 0 > write(i->second, msg.c_str(), msg.size()) )
	{	
		cout<<" write to "<< i->first <<" failed\n";
		return false;
	}
	return true;
}
