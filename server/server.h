#ifndef _tcpserver_module_for_listening_request_support_icommodule_2017
#define _tcpserver_module_for_listening_request_support_icommodule_2017

#include "../classes/funcdisp.hpp"
#include "../classes/singleton.hpp"
#include "../classes/tcpserver.h"
#include <thread>

class Server: public FuncDisp<Server>, public TCPServer
{
protected:
	typedef map<string, thread> THRDMAP;

	THRDMAP _thrdmap;

	bool _getstr;

	void ServerStart(STRARR& cmd);
	void ServerStop(STRARR& cmd);
	
	static void thread_wait_connection(Server*);
	static void thread_get_string(Server*, const string& ip);

	thread _thd;
	virtual void OnGetRemoteString(const string& ip, const string& msg);

public:
	Server();
	virtual ~Server();
	virtual string GetModuleDesc(){ return "tcp server"; }

	// tcpserver
	virtual void OnConnect(string ip, int sck);
	
};

#endif
