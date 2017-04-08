#ifndef _tcpclient_for_connect_to_server_2017_0330
#define _tcpclient_for_connect_to_server_2017_0330

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>
#include <netdb.h>
#include <map>

using namespace std;

class TCPClient
{
protected:	
	typedef map<string, int> SCKMAP;

	SCKMAP _sckmap; 

	int _bufSz;
public:
	TCPClient();
	virtual ~TCPClient();
	bool Connect(string ip, int port);
	bool Send(string msg);

	void CloseAll();
};

#endif
