#include "server.h"
#include "../classes/tool.h"

extern "C" IModule* GetModule()
{
	return Singleton<Server>::GetInstance();
}

Server::Server()
:_getstr(true)
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
		_thd = thread(thread_wait_connection, this);
		cout<<"Server started.\n";
	}
}

void Server::thread_wait_connection(Server* pThis)
{
	pThis->WaitForConnection();
}

void Server::thread_get_string(Server* pThis, const string& ip)
{
	string msg;
	int sz = pThis->_bufSz;
	do
	{
		string buf(sz, 0);
		int n = read(pThis->_sckmap[ip], (char*)&(*buf.begin()), sz);
		rtrim( buf, string(1,0) );
		msg += buf;
		if (n < sz)
		{
			pThis->OnGetRemoteString(ip, msg);
			msg.clear();
		}
	}
	while(pThis->_getstr);
}

void Server::ServerStop(STRARR& cmd)
{
	cout<<"Server stoped.\n";
}

void Server::OnConnect(string ip, int sck)
{
	cout << ip << " connected. \n";
	
	_thrdmap[ip] = thread(thread_get_string, this, ip);
}

void Server::OnGetRemoteString(const string& ip, const string& msg)
{
	cout<< ip << ":" << msg <<" len:"<< msg.size()<< '\n';
	Invoke(msg);
}
