#ifndef _tcpserver_module_for_listening_request_support_icommodule_2017
#define _tcpserver_module_for_listening_request_support_icommodule_2017

#include "funcdisp.hpp"
#include "singleton.hpp"
#include "tcpserver.h"
#include "logfile.h"

#include "session.h"

class Server: public FuncDisp<Server>, public TCPServer, public Thread
{
	bool _run;
	LogFile _log;
	
protected:
	typedef map<int, Session*> SIMAP;

	SIMAP _simap;

	void ServerStart(STRARR& cmd);
	void ServerStop(STRARR& cmd);
	
	void StopSession(STRARR& cmd);
	void DispSession(STRARR& cmd);

	static void OnSessionCallback(string msg, int sck, int signal, void*);

public:
	Server();
	virtual ~Server();
	virtual string GetModuleDesc(){ return "tcp server"; }

	void DeleteSession(int sck);

	// tcpserver
	virtual void OnConnect(string ip, int sck);
	
	// thread
	virtual void run();
};

#endif
