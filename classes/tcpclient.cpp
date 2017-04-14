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
	for( SCKINFO::iterator i = _sckinfo.begin(); i != _sckinfo.end(); ++i )
		close(i->first);

	_sckmap.clear();
	_addrinfo.clear();
}

int TCPClient::Connect(string ip, int port)
{
	cout<<"connecting to "<<ip<<":"<<port<<"...";
	int sck = socket(AF_INET, SOCK_STREAM, 0);

	if (sck<0){ cout<<"socket init err!\n"; return sck;}
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
	_sckmap[ip].push_back(sck);
	_sckinfo[sck] = serv_addr;

	SessionInfo si = {sck, ip, port};
	_sesInfo[sck] = si;

	cout <<"ok.\n";

	return sck;
}

void TCPClient::ShowConnectStatus()
{
	for( SESINFO::iterator i = _sesInfo.begin(); i != _sesInfo.end(); ++i )
		i->second.Show();
}

/* 關閉連線socket  */
bool TCPClient::Close(int sck)
{
	SCKINFO::iterator i = _sckinfo.find(sck);
	if ( i != _sckinfo.end() )
	{
		close(sck);
		_sckinfo.erase(i);
		_sesInfo.erase(sck);
		for( SCKMAP::iterator s = _sckmap.begin(); s != _sckmap.end(); ++s )
			for(list<int>::iterator c = s->second.begin(); c != s->second.end(); ++c)
				if (*c == sck){
					s->second.erase(c);
					if ( !s->second.size() )
						_sckmap.erase(s);
					break;
				}
		return true;
	}
	return false;
}

/* 關閉連線ip  */
bool TCPClient::Close(string ip)
{
	SCKMAP::iterator i = _sckmap.find(ip);
	if ( i != _sckmap.end() )
	{
		for(list<int>::iterator c = i->second.begin(); c != i->second.end(); ++c)
		{
			Close(*c);
			_sckinfo.erase(*c);
		}

		_sckmap.erase(i);
		
		return true;
	}
	return false;
}

bool TCPClient::Send(int sck, string msg)
{
	SCKINFO::iterator i = _sckinfo.find(sck);
	if (i == _sckinfo.end() || !CheckSocket(sck)) return false;

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

	if (i == _sckmap.end()) 
	{
		cout << "socket for "<<ip<<" not found.\n";
		return false;
	}
	cout <<"send to ,sck.size="<<i->second.size()<<"\n";
	for( list<int>::iterator c = i->second.begin(); c != i->second.end(); ++c )
		if ( !CheckSocket(*c) ||  0 >= write(*c, msg.c_str(), msg.size()) )
			cout<<" write to "<< ip <<" failed\n";
	return true;
}

bool TCPClient::CheckSocket(int sck)
{
	pollfd fd = {sck, POLLOUT, 0};

	if ( 0 >= poll(&fd, 1, 500) )
	{
		cout <<"socket ["<<sck<<"] is invalid.\n";
		Close(sck);	
		return false;
	}
	else if (fd.revents & (POLLERR|POLLHUP|POLLNVAL))
	{
		cout<<"socket error\n";
		Close(sck);
		return false;		
	}
	cout<<"CheckSocket ok.\n";

	return true;
}

const list<addrinfo>& TCPClient::GetAddrInfo(string host, string port)
{
	addrinfo hints, *res;

	memset(&hints, 0, sizeof(addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	_addrinfo[host].clear();
	if ( 0 != getaddrinfo( host.size()? host.c_str(): NULL, port.size()? port.c_str(): NULL, &hints, &res ) )
		cout<<"Address info of "<<host<<" doesn't get.\n";

	for( addrinfo *p = res; p; p = p->ai_next )
		_addrinfo[host].push_back(*p)  ;

	freeaddrinfo(res);

	return _addrinfo[host];
}

void SessionInfo::Show()
{
	cout<<"Session:"<<sck<<"\n";
	cout<<"\tIP:"<<ip<<"\n\tPort:"<<port<<"\n";
}

