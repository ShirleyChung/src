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
	AddFunc("closeconnect", &Client::Close);
}

Client::~Client(){}

void Client::Connect(STRARR& cmd)
{
	if (cmd.size()>1)
	{
		TCPClient::Connect(cmd[0], atoi( cmd[1].c_str() ));
	}
	else
		ConnectLocal(cmd);
}

void Client::ConnectStatus(STRARR& cmd)
{
	TCPClient::ShowConnectStatus();
}

void Client::ConnectLocal(STRARR& cmd)
{
	int port = cmd.size()>0? atoi(cmd[0].c_str()): 5000;
	TCPClient::Connect("127.0.0.1", port);
}

void Client::Send(STRARR& cmd)
{
	if (cmd.size()>1)
		TCPClient::Send(cmd[0], Tokencombine(STRARR(cmd.begin()+1, cmd.end())));
	else
		TCPClient::Send("127.0.0.1", Tokencombine(cmd));
}

void Client::Close(STRARR& cmd)
{
	if (cmd.size())
	{
		int sck = atoi(cmd[0].c_str());
		TCPClient::Close(sck);
	}
	else
		cout <<"closeconnect [socketid]\n";
}
