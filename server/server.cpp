#include "server.h"
#include "../classes/tool.h"

extern "C" IModule* GetModule()
{
	return Singleton<Server>::GetInstance();
}

Server::Server()
{
	_name = "server";
	AddFunc("startserver", &Server::ServerStart);
	AddFunc("stopserver", &Server::ServerStop);
	AddFunc("stopses", &Server::StopSession);
	AddFunc("sesinfo", &Server::DispSession);
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
		_thd = thread(thread_wait_connection, this);
		cout<<"Server started.\n";
	}
}

void Server::thread_wait_connection(Server* pThis)
{
	pThis->WaitForConnection();
//	pThis->ListenConnection();
}

void Server::thread_get_string(Server* pThis, int sck)
{
	string msg;
	int sz = pThis->_bufSz;
	cout<<"beRun:"<<pThis->_simap[sck].run<<'\n';
	while(pThis->_simap[sck].run)
	{
		pollfd fd = {sck, POLLIN, 0};
		if ( 0 >= poll(&fd, 1, 1000) ) continue;
		if (fd.revents & (POLLERR|POLLHUP|POLLNVAL)) break;

		string buf(sz, 0);
		int n = read(sck, (char*)&(*buf.begin()), sz);
		if (!n) break;
		rtrim( buf, string(1,0) );
		msg += buf;
		if (n < sz)
		{
			pThis->OnGetRemoteString(sck, msg);
			msg.clear();
		}
	}
	pThis->CloseSession(sck);
	cout<<"server end getstring\n";
}

void Server::ServerStop(STRARR& cmd)
{
	CloseAllSession();
	_serverCfg.pop_back();
	cout<<"Server stoped.\n";
}

void Server::StopSession(STRARR& cmd)
{
	if (cmd.size()>0)
	{
		int sck = atoi(cmd[0].c_str());
		CloseSession(sck);
	}
	else
		cout<<"stopses [sck]\n";
}

void Server::CloseSession(int sck)	
{
	TCPServer::CloseSession(sck);
	_simap.erase(sck);	
}

void Server::DispSession(STRARR& cmd)
{
	for (SIMAP::iterator i = _simap.begin(); i != _simap.end(); ++i)
		i->second.ShowInfo();
}

void Server::OnConnect(string ip, int sck)
{
	cout << ip << " connected. \n";
	
	_simap[sck].sck = sck;
	_simap[sck].ip = ip;
	_simap[sck].run = true;	
	_simap[sck].thd = thread(thread_get_string, this, sck);
}

void Server::OnGetRemoteString(int sck, const string& msg)
{
	cout<< "socket["<<sck<<"]:"<< msg <<" len:"<< msg.size()<< '\n';
	Invoke(msg);
}


