#ifndef _tcp_Server_cpp_class_2017_sly_initi_
#define _tcp_Server_cpp_class_2017_sly_initi_

#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <string>
#include <unistd.h>
#include <map>
#include <list>
#include <sys/poll.h>

using namespace std;

struct SocketInfo : sockaddr_in
{
	string ip;
	SocketInfo(const sockaddr_in& saddr):sockaddr_in(saddr){};
	SocketInfo(){};
};

struct ServerCfg{
	int sck;
	int port;
	int lsnum;
	bool bwait;
	
	ServerCfg():sck(-1), bwait(false){};
	~ServerCfg(){}
};

class TCPServer{

protected:
	typedef map<string, int> SCKMAP;
	typedef map<int , SocketInfo> SCKINFO;
	SCKMAP _sckmap;
	SCKINFO _sckinfo;

	list<ServerCfg> _serverCfg; //server socket
	
	int _lsnNum; //listen numbers
	size_t _bufSz; //recv buffer size

	sockaddr_in _sckaddr;

	void WaitForConnection();

	bool ListenConnection();

	void CloseSession(string ip);

	void CloseSession(int sck);

	void CloseAllSession();

	virtual void OnConnect(string ip, int sck) = 0;

public:
	TCPServer();
	virtual ~TCPServer();

	bool Init(int port);

	int Send(string ip, string msg);
	int Send(int sck, string msg);

	int Recv(string ip, string& msg);
	int Recv(int sck, string& msg);
};

#endif
