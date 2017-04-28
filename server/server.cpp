#include "server.h"
#include "tool.h"
#include <stdlib.h>

extern "C" IModule* GetModule()
{
	return Singleton<Server>::GetInstance();
}

Server::Server()
:_run(true)
,_log("./logs/server.log")
{
	_name = "server";
	AddFunc("ss", &Server::ServerStart);
	AddFunc("startserver", &Server::ServerStart);
	AddFunc("stopserver", &Server::ServerStop);
	AddFunc("closes", &Server::StopSession);
	AddFunc("si", &Server::DispSession);
	AddFunc("sesinfo", &Server::DispSession);
}

Server::~Server()
{
	for( SIMAP::iterator i = _simap.begin(); i != _simap.end(); ++i )
		delete i->second;
	_simap.clear();
}

void Server::ServerStart(STRARR& cmd)
{
	int port = 5000;
	if (cmd.size() > 0)
		port = atoi(cmd[0].c_str());

	if (!Init(port))
		cout<<"port "<<port<<" cannot be initialed.\n";
	else
	{
		start();
		cout<<"Server started.\n";
		_log<<"Server started.";
	}
}

void Server::run()
{
	TCPServer::WaitForConnection();
}

void Server::ServerStop(STRARR& cmd)
{
	_serverCfg.pop_back();
	stop();
	cout<<"Server stoped.\n";
}

void Server::StopSession(STRARR& cmd)
{
	if (cmd.size()>0)
	{
		int sck = atoi(cmd[0].c_str());
		DeleteSession(sck);
	}
	else
		cout<<"stopses [sck]\n";
}

void Server::DeleteSession(int sck)	
{
	SIMAP::iterator i = _simap.find(sck);
	if (i != _simap.end())
	{
		delete i->second;
		_simap.erase(i);	
	}
}

void Server::DispSession(STRARR& cmd)
{
	for (SIMAP::iterator i = _simap.begin(); i != _simap.end(); ++i)
		i->second->ShowInfo();
}

void Server::OnConnect(string ip, int sck)
{
	cout << ip << " connected at ["<<sck<<"]\n";

	Session* psi = new Session(sck, ip, (void*)this);
	psi->SetCallback(OnSessionCallback, (void*)this);
	_simap[sck] = psi;
	
	psi->start();
}

void Server::OnSessionCallback(string msg, int sck, int signal, void* pt)
{
	Server* pthis = (Server*)pt;
	
	cout<< "OnSessionCallback["<<sck<<"]:"<< msg << '\n';
	switch(signal)
	{
		case Session::NEWMSG:
			rtrim(msg, "\r\n");
			pthis->Invoke(msg);
			break;
		case Session::ENDSES:
			pthis->DeleteSession(sck);
			break;
			default:;
	};
}