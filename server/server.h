#ifndef _tcpserver_module_for_listening_request_support_icommodule_2017
#define _tcpserver_module_for_listening_request_support_icommodule_2017

#include "../classes/funcdisp.h"
#include "../classes/tcpserver.h"

#include <thread>

class Server: public FuncDisp<Server>, public TCPServer
{
	static Server* _inst;
	void ServerStart(STRARR& cmd);
	void ServerStop(STRARR& cmd);
	
	static void thread_proc(Server*);

	thread _thd;
	Server();
public:
	static Server* GetModuleInst(){ if(_inst) return _inst; else{ _inst = new Server(); return _inst; } } 
	virtual string GetModuleDesc(){ return "tcp server"; }
	
};

#endif
