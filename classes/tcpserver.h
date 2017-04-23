#ifndef _tcp_Server_cpp_class_2017_sly_initi_
#define _tcp_Server_cpp_class_2017_sly_initi_

#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <memory.h>
#include <string>
#include <map>
#include <list>


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

	sockaddr_in _sckaddr;

	void WaitForConnection();

	bool ListenConnection();

	virtual void OnConnect(string ip, int sck) = 0;

public:
	TCPServer();
	virtual ~TCPServer();

	bool Init(int port);
};

#endif
