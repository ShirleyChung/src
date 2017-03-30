#include "tcpclient.h"
#include <iostream>
#include <arpa/inet.h>

TCPClient::TCPClient()
{}

bool TCPClient::Connect(string ip, ushort port)
{
	_clisck = socket(AF_INET, SOCK_STREAM, 0);
	if (_clisck<0){ cout<<"socket init err!\n"; return false;}
	in_addr ipv4addr;
	sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr.s_addr);
	serv_addr.sin_port = htons(port);
	if ( 0 != connect(_clisck, (sockaddr*)&serv_addr, sizeof(serv_addr)) )
	{
		cout<<" connect error!\n";
		return false;
	}

	return true;
}

bool TCPClient::SendTo(int socket, string msg)
{
	write(_clisck, msg.c_str(), msg.size());
	return true;
}
