#ifndef _tcpserver_module_for_listening_request_support_icommodule_2017
#define _tcpserver_module_for_listening_request_support_icommodule_2017

#include "../classes/funcdisp.hpp"
#include "../classes/singleton.hpp"
#include "../classes/tcpserver.h"
#include <pthread.h>

struct SessionInfo
{
	int sck;
	string ip;
	bool run;
	pthread_t thd;
	void* pt;

	SessionInfo():run(true){};

	void ShowInfo(){
		cout<<"socket:"<<sck<<"\n\tIP:"<<ip<<"\n\trunning:"<<run<<'\n';
	}
};

class Server: public FuncDisp<Server>, public TCPServer
{
protected:
	typedef map<int, SessionInfo*> SIMAP;

	SIMAP _simap;

	void ServerStart(STRARR& cmd);
	void ServerStop(STRARR& cmd);
	void StopSession(STRARR& cmd);
	void DispSession(STRARR& cmd);
	
	static void* thread_wait_connection(void*);
	static void* thread_get_string(void*);

	pthread_t _thd;
	virtual void OnGetRemoteString(int sck, const string& msg);

public:
	Server();
	virtual ~Server();
	virtual string GetModuleDesc(){ return "tcp server"; }

	void CloseSession(int sck);

	// tcpserver
	virtual void OnConnect(string ip, int sck);
	
};

#endif
