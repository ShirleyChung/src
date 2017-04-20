#include "server.h"
#include "../classes/tool.h"
#include <system_error>

extern "C" IModule* GetModule()
{
	return Singleton<Server>::GetInstance();
}

Server::Server()
{
	_name = "server";
	AddFunc("ss", &Server::ServerStart);
	AddFunc("startserver", &Server::ServerStart);
	AddFunc("stopserver", &Server::ServerStop);
	AddFunc("closes", &Server::StopSession);
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
		pthread_create( &_thd, NULL, thread_wait_connection, (void*)this);
		cout<<"Server started.\n";
	}
}

void* Server::thread_wait_connection(void* pThis)
{
	((Server*)pThis)->WaitForConnection();
//	pThis->ListenConnection();
}

void* Server::thread_get_string(void* pt)
{
	cout<<"=>thread get string start.\n ";
	SessionInfo* pinfo = (SessionInfo*)pt;
	string msg;
	Server* pThis = (Server*)pinfo->pt;
	int sz = pThis->_bufSz;
	int sck = pinfo->sck;
	
	cout<<"beRun:"<<pinfo->run<<'\n';
	while(pinfo->run)
	{
		pollfd fd = {sck, POLLIN, 0};
		if ( 0 >= poll(&fd, 1, 1000) ) continue;
		if (fd.revents & (POLLERR|POLLHUP|POLLNVAL)) break;
		cout<<"reading "<<sck<<"...";
		string buf(sz, 0);
		int n = read(sck, (char*)&(*buf.begin()), sz); //blocked here..
		if (!n) break;
		cout<<" read.\n";
		rtrim( buf, string(1,0) );
		msg += buf;
		cout<<"msg:"<<msg<<"\n";
		if (n < sz)
		{
			pThis->OnGetRemoteString(sck, msg);
			msg.clear();
		}
	}
	cout<<"loop break;";
	pThis->CloseSession(sck);
	cout<<"=>thread get string end.\n";
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
	cout << ip << " connected. \n";

	SessionInfo* psi = new SessionInfo();
	psi->sck = sck;
	psi->ip = ip;
	psi->run = true;	
	psi->pt = (void*)this;
	_simap[sck] = psi;
	pthread_create( &psi->thd, NULL, thread_get_string, (void*)psi);
}

void Server::OnGetRemoteString(int sck, const string& msg)
{
	cout<< "OnGetRemoteString["<<sck<<"]:"<< msg <<" len:"<< msg.size()<< '\n';
	string rmsg = msg;
	rtrim(rmsg, "\r\n");
	Invoke(rmsg);
}