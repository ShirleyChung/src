#ifndef _tcpclient_for_connect_to_server_2017_0330
#define _tcpclient_for_connect_to_server_2017_0330

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>
#include <netdb.h>

using namespace std;

class TCPClient
{
	typedef unsigned short ushort;

	int _clisck;
public:
	TCPClient();
	bool Connect(string, ushort port);
	bool SendTo(int socket, string msg);
};

#endif
