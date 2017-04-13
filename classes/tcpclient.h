#ifndef _tcpclient_for_connect_to_server_2017_0330
#define _tcpclient_for_connect_to_server_2017_0330

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>
#include <netdb.h>
#include <map>
#include <list>
#include <sys/poll.h>

using namespace std;

class TCPClient
{
protected:	
	typedef map<string, list<int> > SCKMAP; /* ip:sck  */
	typedef map<int, sockaddr_in> SCKINFO;  /* sck, sckaddr */

	SCKMAP _sckmap; 
	SCKINFO _sckinfo;

	int _bufSz;

protected:
	typedef map<string, list<addrinfo> > ADDRINFO; /* sck, addr-list */
	ADDRINFO _addrinfo;

public:
	TCPClient();
	virtual ~TCPClient();
	int Connect(string ip, int port);
	bool Send(int sck, string msg);
	bool Send(string ip, string msg);
	
	bool CheckSocket(int sck);

	const list<addrinfo>& GetAddrInfo(string host, string port);

	void CloseAll();
	bool Close(string ip);
	bool Close(int sck);
};

#endif
