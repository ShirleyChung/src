#include "client.h"
#include <stdlib.h>
#include "../classes/tool.h"

extern "C" IModule* GetModule()
{
	return (IModule*)(new Client());
}

Client::Client()
{
	_name = "client";
	AddFunc("connect", &Client::Connect);
	AddFunc("send", &Client::Send);
}

void Client::Connect(STRARR& cmd)
{
	if (cmd.size()>1)
	{
		int port = atoi(cmd[1].c_str());
		TCPClient::Connect(cmd[0], port);
	}
	else
		cout<<"usage: connect ip port\n";
}

void Client::Send(STRARR& cmd)
{
	string msg = Tokencombine(cmd);
	TCPClient::Send(msg);
}
