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
}

void Server::thread_get_string(Server* pThis, int sck)
{
	string msg;
	int sz = pThis->_bufSz;
	do
	{
		string buf(sz, 0);
		int n = read(sck, (char*)&(*buf.begin()), sz);
		rtrim( buf, string(1,0) );
		msg += buf;
		if (n < sz)
		{
			pThis->OnGetRemoteString(sck, msg);
			msg.clear();
		}
	}
	while(pThis->_simap[sck].run);
	close(sck);
}

void Server::ServerStop(STRARR& cmd)
{
	cout<<"Server stoped.\n";
}

void Server::StopSession(STRARR& cmd)
{
	if (cmd.size()>0)
	{
		int sck = atoi(cmd[0].c_str());
		if (_simap.find(sck) != _simap.end())
		{
			_simap[sck].run = false;
			pthread_cancel(_simap[sck].thd.native_handle());
			_simap.erase(sck);
		}
	}
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
	_simap[sck].thd = thread(thread_get_string, this, sck);
}

void Server::OnGetRemoteString(int sck, const string& msg)
{
	cout<< "socket["<<sck<<"]:"<< msg <<" len:"<< msg.size()<< '\n';
	Invoke(msg);
}


