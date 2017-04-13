#include "tcpserver.h"
#include <iostream>
#include <memory.h>
#include <arpa/inet.h>
#include <fcntl.h>


TCPServer::TCPServer()
:_lsnNum(5)
,_bufSz(1024)
,_do_wait(true)
,_svrsck(-1)
{
}

TCPServer::~TCPServer()
{
	CloseAllSession();
	if (_svrsck>=0) close(_svrsck);
}

bool TCPServer::Init(int port)
{
	_port = port;
	
	memset(&_sckaddr, 0, sizeof(_sckaddr));

	_sckaddr.sin_family = AF_INET;
	_sckaddr.sin_addr.s_addr = INADDR_ANY;
	_sckaddr.sin_port = htons(_port);

	if (_svrsck>=0) close(_svrsck);
	
	_svrsck = socket(AF_INET, SOCK_STREAM, 0);
	if (_svrsck <0)
	{
		cout<<" socket open error!\n";
		return false;
	}
	
	if (0 != bind(_svrsck, (sockaddr*)&_sckaddr, sizeof(_sckaddr)))
	{	
		cout<<"bind "<<_port<<" error.\n";
		return false;
	}
	return true;
}

void TCPServer::Echo()
{
	listen(_svrsck, _lsnNum);
	cout<<" listening port:"<<_port<<" ,socket:"<<_svrsck<<"\n";
	sockaddr_in cliaddr;
	socklen_t clilen = sizeof(sockaddr);
	int newsck = accept(_svrsck, (sockaddr*)&cliaddr, &clilen);	
	if (newsck<0) cout<<" accept failed!\n";
	else
		cout<<"Accepted.\n";

	char* buf = new char[_bufSz];
	string msg, ret = "I got it";
	do
	{
		memset(buf, 0, _bufSz);
		int n = read(newsck, buf, _bufSz);
		msg = buf;
		cout<<"msg="<<msg<<", sizeof msg="<<msg.size()<<'\n';
		n = write(newsck, ret.c_str(), ret.size());
	}while( msg != "ok");
	
	close(newsck);
	cout<<" socket "<<newsck<<" closed.\n";

	delete[] buf;
}

/* block waiting conection  */
void TCPServer::WaitForConnection()
{
	listen(_svrsck, _lsnNum);
	cout<<" listening port:"<<_port<<" ,socket:"<<_svrsck<<"\n";
	sockaddr_in cliaddr;
	socklen_t clilen = sizeof(sockaddr);

	_sckmap.clear();

	while(_do_wait)
	{
		pollfd fd = {_svrsck, POLLIN, 0};
		if ( 0 >= poll(&fd, 1, 1000) ) continue;

		int sck = accept(_svrsck, (sockaddr*)&cliaddr, &clilen);	
		if (sck<0)
			cout<<" accept failed!\n";
		else
		{
			cout<<"Accepted.\n";
			string cip(INET_ADDRSTRLEN+1, 0);

			inet_ntop(AF_INET, &cliaddr.sin_addr, (char*)&(*cip.begin()), INET_ADDRSTRLEN);
			_sckmap[cip] = sck;
			_sckinfo[sck] = cliaddr;

			OnConnect(cip, sck);
		}
	}
}

/* use select to implement non-blocking connection */
bool TCPServer::ListenConnection()
{
	fd_set fds, fds_tmp;
	timeval timeout={1,0};
	int maxsck = _svrsck;
	sockaddr_in cliaddr;
	socklen_t addrlen;

	FD_ZERO(&fds);
	FD_ZERO(&fds_tmp);

	FD_SET(_svrsck, &fds);
	listen(_svrsck, _lsnNum);
	cout<<"listening "<<_lsnNum<<"\n";
	while(_do_wait)
	{
		fds_tmp = fds;

		if ( 0 >= select(maxsck + 1, &fds_tmp/*read*/, NULL/*write*/, NULL/*except*/, &timeout/*timeout*/))
			continue;

		for(int sck = 0; sck <= maxsck; ++sck)
		{
			if (FD_ISSET(sck, &fds_tmp))
			{
				if (sck==_svrsck)
				{
					//new connection
					int newsck = accept(_svrsck, (sockaddr*)&cliaddr, &addrlen);
					FD_SET(newsck, &fds);
					if (newsck > maxsck) 
						maxsck = newsck;
					cout<<"new client connected.\n";

					string cip(INET_ADDRSTRLEN+1, 0);
					inet_ntop(AF_INET, &cliaddr.sin_addr, (char*)&(*cip.begin()), INET_ADDRSTRLEN);
					_sckmap[cip] = sck;
					_sckinfo[sck] = cliaddr;
				}
				else
				{
					//data from client.
					string buf(_bufSz, 0);
					if ( recv(sck, (char*)&(*buf.begin()), _bufSz, 0) <=0 )
					{
						// client closed.
						close(sck);
						FD_CLR(sck, &fds);
					}
					else
					{
						string cip(INET_ADDRSTRLEN+1, 0);
						inet_ntop(AF_INET, &_sckinfo[sck].sin_addr, (char*)&(*cip.begin()), INET_ADDRSTRLEN);
						OnConnect(cip, sck);
					}
				}
			}
			else
			{
			}
		}
	}

	return true;
}

bool TCPServer::PeekConnection()
{
	timeval timeout={1,0};
	listen(_svrsck, _lsnNum);
	
	while(_do_wait)
	{
		pollfd pfd = {_svrsck, POLLIN, 0};
		if ( poll(&pfd, 1, 1000) >0 )
		{
			sockaddr_in cliaddr;
			socklen_t addrlen;
			int sck = accept(_svrsck, (sockaddr*)&cliaddr, &addrlen);
			cout<<"new client connected.\n";

			string cip(INET_ADDRSTRLEN+1, 0);
			inet_ntop(AF_INET, &cliaddr.sin_addr, (char*)&(*cip.begin()), INET_ADDRSTRLEN);
			_sckmap[cip] = sck;
			_sckinfo[sck] = cliaddr;
			OnConnect(cip, sck);
		}
	}

	return true;
}

void TCPServer::CloseSession(string ip)
{
	SCKMAP::iterator i = _sckmap.find(ip);
	if (i != _sckmap.end() )

	{
		close(i->second);
		_sckinfo.erase(i->second);
		_sckmap.erase(i);
	}
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
