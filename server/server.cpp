#include "server.h"

extern "C" IModule* GetModule()
{
	return (IModule*)(new Server());
}

Server::Server()
{
	_name = "server";
	AddFunc("startserver", &Server::ServerStart);
	AddFunc("stopserver", &Server::ServerStop);
}

void Server::ServerStart(STRARR& cmd)
{
	int port = 5000;
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
	pThis->Echo();
}

void Server::ServerStop(STRARR& cmd)
{
	cout<<"Server stoped.\n";
}
