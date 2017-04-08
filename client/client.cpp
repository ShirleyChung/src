#include "client.h"
#include <stdlib.h>
#include "../classes/tool.h"

extern "C" IModule* GetModule()
{
	return Singleton<Client>::GetInstance();
}

Client::Client()
{
	_name = "client";
	AddFunc("connect", &Client::Connect);
	AddFunc("connectlocal", &Client::ConnectLocal);
	AddFunc("cstatus", &Client::ConnectStatus);
	AddFunc("send", &Client::Send);
}

Client::~Client(){}

void Client::Connect(STRARR& cmd)
{
	if (cmd.size()>1)
	{
		SessionInfo si;
		si.ip = cmd[0];
		si.port = atoi(cmd[1].c_str());
		si.sck =TCPClient::Connect(si.ip, si.port);
		if (si.sck >=0)
			_sesInfo.push_back(si);
	}
	else
		ConnectLocal(cmd);
}

void Client::ConnectStatus(STRARR& cmd)
{
	for( list<SessionInfo>::iterator i = _sesInfo.begin(); i != _sesInfo.end(); ++i )
		(*i).Show();

}

void Client::ConnectLocal(STRARR& cmd)
{
	SessionInfo si;
	si.ip = "127.0.0.1";
	si.port = cmd.size()>0? atoi(cmd[0].c_str()): 5000;
	si.sck = TCPClient::Connect(si.ip, si.port);
	if (si.sck >=0)	
		_sesInfo.push_back(si);
}

void Client::Send(STRARR& cmd)
{
	if (cmd.size()>1)
		TCPClient::Send(cmd[0], Tokencombine(STRARR(cmd.begin()+1, cmd.end())));
	else
		TCPClient::Send("127.0.0.1", Tokencombine(cmd));
}

void SessionInfo::Show()
{
	cout<<"Session:"<<sck<<"\n";
	cout<<"\tIP:"<<ip<<"\n\tPort:"<<port<<"\n";
}
