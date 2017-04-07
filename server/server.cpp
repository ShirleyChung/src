#include "server.h"

extern "C" IModule* GetModule()
{
	return Singleton<Server>::GetInstance();
}

Server::Server()
{
	_name = "server";
	AddFunc("startserver", &Server::ServerStart);
	AddFunc("stopserver", &Server::ServerStop);
}

Server::~Server()
{}

void Server::ServerStart(STRARR& cmd)
{
	int port = 5000;
	if (cmd.size() > 0)
		port = atoi(cmd[0].c_str());

	if (!Init(port))
		cout<<"port "<<port<<" cannot be initialed.\n";
	else
	{
		_thd = thread(thread_proc, this);
		cout<<"Server started.\n";
	}
}

void Server::thread_proc(Server* pThis)
{
	pThis->WaitForConnection();
}

void Server::ServerStop(STRARR& cmd)
{
	cout<<"Server stoped.\n";
}

void Server::OnConnect(string ip, int sck)
{
	
}
