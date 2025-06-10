#include "tcpserver.h"
#include <iostream>
#include <memory.h>
#include <fcntl.h>

TCPServer::TCPServer()
:_lsnNum(5)
{
}

TCPServer::~TCPServer()
{
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

	setsockopt(cfg.sck, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));
	
	if (0 > ::bind(cfg.sck, (sockaddr*)&_sckaddr, sizeof(_sckaddr)))
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
			_sckinfo[sck] = SocketInfo(cliaddr, cip);

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
					_sckinfo[newsck] = SocketInfo(cliaddr, cip);
					OnConnect(cip, newsck);	
			}
	}

	return true;
}