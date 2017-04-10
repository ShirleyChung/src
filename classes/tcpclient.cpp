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
<<<<<<< HEAD
=======
}

void TCPClient::CloseAll()
{
	for( SCKMAP::iterator i = _sckmap.begin(); i != _sckmap.end(); ++i )
		close(i->second);
	_sckmap.clear();
>>>>>>> 0104eb1c5e53fa2a7714bb0c1c0bc79e83c0b2cc
}

void TCPClient::CloseAll()
{
<<<<<<< HEAD
	for( SCKMAP::iterator i = _sckmap.begin(); i != _sckmap.end(); ++i )
		close(i->second);
	_sckmap.clear();
	_sckinfo.clear();
}

int TCPClient::Connect(string ip, int port)
{
	cout<<"connecting to "<<ip<<":"<<port<<"...";
	int sck = socket(AF_INET, SOCK_STREAM, 0);

	if (sck<0){ cout<<"socket init err!\n"; return sck;}
=======
	int sck = socket(AF_INET, SOCK_STREAM, 0);
	_sckmap[ip] = sck;

	if (sck<0){ cout<<"socket init err!\n"; return false;}
>>>>>>> 0104eb1c5e53fa2a7714bb0c1c0bc79e83c0b2cc
	in_addr ipv4addr;
	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr.s_addr);
	serv_addr.sin_port = htons(port);
	if ( 0 > connect(sck, (sockaddr*)&serv_addr, sizeof(serv_addr)) )
	{
		cout<<" connect error!\n";
		return -1;
	}
	_sckmap[ip] = sck;
	_sckinfo[sck] = serv_addr;
	cout <<"ok.\n";

	return sck;
}

bool TCPClient::Close(int sck)
{
	SCKINFO::iterator i = _sckinfo.find(sck);
	if ( i != _sckinfo.end() )
	{
		Close(sck);
		_sckinfo.erase(i);
		for( SCKMAP::iterator s = _sckmap.begin(); s != _sckmap.end();)
			if (s->second == sck){
				_sckmap.erase(s); s = _sckmap.begin();
			}
			else ++s;
		return true;
	}
	return false;
}

bool TCPClient::Close(string ip)
{
	SCKMAP::iterator i = _sckmap.find(ip);
	if ( i != _sckmap.end() )
	{
		Close(i->second);
		_sckmap.erase(i);
		_sckinfo.erase(i->second);
		return true;
	}
	return false;
}

bool TCPClient::Send(int sck, string msg)
{
	SCKINFO::iterator i = _sckinfo.find(sck);
	if (i == _sckinfo.end()) return false;

	if ( 0 > write(sck, msg.c_str(), msg.size()) )
	{
		cout<<" write to "<< i->first <<" failed\n";
		return false;
	}
	return true;
}

bool TCPClient::Send(string ip, string msg)
{
	SCKMAP::iterator i = _sckmap.find(ip);
	if (i == _sckmap.end()) return false;

	if ( 0 > write(i->second, msg.c_str(), msg.size()) )
	{
		cout<<" write to "<< i->first <<" failed\n";
		return false;
	}
	return true;
}
