#ifndef _tcp_Server_cpp_class_2017_sly_initi_
#define _tcp_Server_cpp_class_2017_sly_initi_

#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <string>
#include <unistd.h>

using namespace std;

class TCPServer{

protected:

	int _port;
	int _svrsck; //server socket
	int _lsnNum; //listen numbers
	size_t _bufSz; //recv buffer size

	sockaddr_in _sckaddr;

public:
	TCPServer();
	virtual ~TCPServer();

	bool Init(int port);

	void Echo();
};

#endif
