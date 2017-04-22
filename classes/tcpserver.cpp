#include "tcpserver.h"
#include <iostream>
#include <memory.h>
#include <arpa/inet.h>
#include <fcntl.h>

TCPServer::TCPServer()
:_lsnNum(5)
,_bufSz(1024)
{
}

TCPServer::~TCPServer()
{
	CloseAllSession();
	list<ServerCfg>::iterator i = _serverCfg.begin();
	for( ; i != _serverCfg.end(); ++i )
		close((*i).sck);
	_serverCfg.clear();
}

bool TCPServer::Init(int port)
{
	ServerCfg cfg;
	cfg.port = port;
	cfg.bwait = true;
	cfg.lsnum = _lsnNum;
	
	memset(&_sckaddr, 0, sizeof(_sckaddr));

	_sckaddr.sin_family = AF_INET;
	_sckaddr.sin_addr.s_addr = INADDR_ANY;
	_sckaddr.sin_port = htons(cfg.port);
	
	cfg.sck = socket(AF_INET, SOCK_STREAM, 0);
	if ( 0 > cfg.sck)
	{
		cout<<" socket open error!\n";
		return false;
	}
	
	int optval = 1;
	setsockopt(cfg.sck, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	
	if (0 > bind(cfg.sck, (sockaddr*)&_sckaddr, sizeof(_sckaddr)))
	{	
		cout<<"bind "<<cfg.port<<" error.\n";
		return false;
	}
	
	_serverCfg.push_back(cfg);
	return true;
}

/* block waiting conection  */
void TCPServer::WaitForConnection()
{
	if (!_serverCfg.size()) return;
		
	ServerCfg& cfg = _serverCfg.back();

	if ( 0 > listen(cfg.sck, cfg.lsnum) )
	{
		cout<<"listen "<<cfg.sck<<", backlog:"<<cfg.lsnum<<" failed.\n";
		return;
	}
	cout<<" listening port:"<<cfg.port<<" ,socket:"<<cfg.sck<<"\n";
	sockaddr_in cliaddr;
	socklen_t clilen = sizeof(sockaddr);

	while(cfg.bwait)
	{
		pollfd fd = {cfg.sck, POLLIN, 0};
		if ( 0 >= poll(&fd, 1, 1000) ) continue;

		int sck = accept(cfg.sck, (sockaddr*)&cliaddr, &clilen);	
		cout<<"accept: "<<sck<<"\n";
		if (sck<0)
			cout<<" accept failed!\n";
		else
		{
			cout<<"Accepted.\n";
			string cip(INET_ADDRSTRLEN+1, 0);

			inet_ntop(AF_INET, &cliaddr.sin_addr, (char*)&(*cip.begin()), INET_ADDRSTRLEN);
			_sckmap[cip] = sck;
			_sckinfo[sck] = SocketInfo(cliaddr);
			_sckinfo[sck].ip = cip;

			OnConnect(cip, sck);
		}
	}
}

/* use select to implement non-blocking connection */
bool TCPServer::ListenConnection()
{
	if (!_serverCfg.size()) return false;
	
	ServerCfg& cfg = _serverCfg.back();
	
	fd_set fds, fdstmp;
	timeval timeout={1,0};

	sockaddr_in cliaddr;
	socklen_t addrlen;

	FD_ZERO(&fds);

	FD_SET(cfg.sck, &fds);
	listen(cfg.sck, cfg.lsnum);
	cout<<"listening "<<cfg.port<<"\n";
	
	while(cfg.bwait)
	{
		fdstmp = fds;
		if ( 0 >= select(cfg.sck + 1, &fdstmp/*read*/, NULL/*write*/, NULL/*except*/, &timeout/*timeout*/))
			continue;

			if (FD_ISSET(cfg.sck, &fdstmp))
			{
					//new connection
					int newsck = accept(cfg.sck, (sockaddr*)&cliaddr, &addrlen);
					FD_SET(newsck, &fds);
					cout<<"new client connected.\n";

					string cip(INET_ADDRSTRLEN+1, 0);
					inet_ntop(AF_INET, &cliaddr.sin_addr, (char*)&(*cip.begin()), INET_ADDRSTRLEN);
					_sckmap[cip] = newsck;
					_sckinfo[newsck] = SocketInfo(cliaddr);
					_sckinfo[newsck].ip = cip;
					OnConnect(cip, newsck);	
			}
	}

	return true;
}

void TCPServer::CloseSession(string ip)
{
	cout<<"Close Session "<<ip;
	SCKMAP::iterator i = _sckmap.find(ip);
	if (i != _sckmap.end() )
	{
		close(i->second);
		_sckinfo.erase(i->second);
		_sckmap.erase(i);
	}
	cout<<" closed.\n";
}

void TCPServer::CloseSession(int sck)
{
	cout<<"CloseSession sck "<<sck;
	SCKINFO::iterator i = _sckinfo.find(sck);
		if (i != _sckinfo.end())
		{
			close(sck);
			_sckmap.erase(i->second.ip);
			_sckinfo.erase(i);
		}
		cout<<" closed.\n";
}

void TCPServer::CloseAllSession()
{
	for( SCKMAP::iterator itor = _sckmap.begin(); itor != _sckmap.end(); ++itor )
		close(itor->second);
	_sckmap.clear();
	_sckinfo.clear();
}

int TCPServer::Send(string ip, string msg)
{
	SCKMAP::iterator i = _sckmap.find(ip);
	if ( i == _sckmap.end()) return -1;

	return write(i->second, msg.c_str(), msg.size());
}

int TCPServer::Send(int sck, string msg)
{
	SCKINFO::iterator i = _sckinfo.find(sck);
	if ( i == _sckinfo.end()) return -1;

	return write(sck, msg.c_str(), msg.size());
}

int TCPServer::Recv(string ip, string& msg)
{
	SCKMAP::iterator i = _sckmap.find(ip);
	if ( i == _sckmap.end()) return -1;

	msg.reserve(_bufSz+1);
	return read(i->second, (char*)&(*msg.begin()), _bufSz);
}

int TCPServer::Recv(int sck, string& msg)
{
	SCKINFO::iterator i = _sckinfo.find(sck);
	if ( i == _sckinfo.end()) return -1;

	msg.reserve(_bufSz+1);
	return read(sck, (char*)&(*msg.begin()), _bufSz);
}
