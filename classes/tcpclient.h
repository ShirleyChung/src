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
	typedef map<int, sockaddr_in> SCKINFO;

	SCKMAP _sckmap; 
	SCKINFO _sckinfo;

	int _bufSz;
public:
	TCPClient();
	virtual ~TCPClient();
	int Connect(string ip, int port);
	bool Send(int sck, string msg);
	bool Send(string ip, string msg);

	void CloseAll();
	bool Close(string ip);
	bool Close(int sck);
};

#endif
