#ifndef _tcpclient_for_connect_to_server_2017_0330
#define _tcpclient_for_connect_to_server_2017_0330

#ifdef posix
	#include <sys/socket.h>
	#include <sys/poll.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <arpa/inet.h>
#else
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#define poll WSAPoll
	#pragma comment(lib, "Ws2_32.lib")	
#endif

#include <unistd.h>
#include <string>
#include <map>
#include <list>

using namespace std;

struct SessionInfo
{
	int sck;
	string ip;
	int port;
	void Show();
};

/* Socket Client 模組 */
/* 連接至指令位址: Connect */
/* 傳送資料      : Send */
class TCPClient
{
protected:	
	typedef map<string, list<int> > SCKMAP; /* ip:sck  */
	typedef map<int, sockaddr_in> SCKINFO;  /* sck, sckaddr */
	typedef map<int, SessionInfo> SESINFO;

	SCKMAP _sckmap; 
	SCKINFO _sckinfo;
	SESINFO _sesInfo;

	int _bufSz;

protected:
	typedef map<string, list<addrinfo> > ADDRINFO; /* sck, addr-list */
	ADDRINFO _addrinfo;

public:
	TCPClient();
	virtual ~TCPClient();
	int Connect(string ip, int port);
	void ShowConnectStatus();

	bool Send(int sck, string msg);
	bool Send(string ip, string msg);
	
	bool CheckSocket(int sck);

	const list<addrinfo>& GetAddrInfo(string host, string port);

	void CloseAll();
	bool Close(string ip);
	bool Close(int sck);
};

#endif
