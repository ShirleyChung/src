#ifndef _tcp_Server_cpp_class_2017_sly_initi_
#define _tcp_Server_cpp_class_2017_sly_initi_

#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <string>
#include <unistd.h>
#include <map>

using namespace std;

class TCPServer{

protected:
	typedef map<string, int> SCKMAP;
	SCKMAP _sckmap;

	int _port;
	int _svrsck; //server socket
	int _lsnNum; //listen numbers
	size_t _bufSz; //recv buffer size
	bool _do_wait; //wait for accept

	sockaddr_in _sckaddr;

	void WaitForConnection();

	void CloseSession(string ip);

	void CloseAllSession();

	virtual void OnConnect(string ip, int sck) = 0;

public:
	TCPServer();
	virtual ~TCPServer();

	bool Init(int port);

	void Echo();

	int Send(string ip, string msg);

	int Recv(string ip, string& msg);
};

#endif
