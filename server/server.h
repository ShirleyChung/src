#ifndef _tcpserver_module_for_listening_request_support_icommodule_2017
#define _tcpserver_module_for_listening_request_support_icommodule_2017

#include "../classes/funcdisp.h"
#include "../classes/tcpserver.h"

#include <thread>

class Server: public FuncDisp<Server>, public TCPServer
{
	void ServerStart(STRARR& cmd);
	void ServerStop(STRARR& cmd);
	
	static void thread_proc(Server*);

	thread _thd;
public:
	Server();
	virtual string GetModuleDesc(){ return "tcp server"; }
	
};

#endif
