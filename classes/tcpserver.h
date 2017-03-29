#ifndef _tcp_Server_cpp_class_2017_sly_initi_
#define _tcp_Server_cpp_class_2017_sly_initi_

#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <string>

using namespace std;

class TCPServer{

	unsigned int _port;
	unsigned int _svrsck; //server socket
	sockaddr_in _sckaddr;

public:
	TCPServer(unsigned int port);
	TCPServer();
	virtual ~TCPServer();

	bool Init();
};

#endif
