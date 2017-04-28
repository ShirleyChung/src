#ifndef _tcpclient_module_for_listening_request_support_icommodule_2017
#define _tcpclient_module_for_listening_request_support_icommodule_2017

#include "funcdisp.hpp"
#include "tcpclient.h"
#include "singleton.hpp"
#include <list>



class Client: public FuncDisp<Client>, public TCPClient
{
protected:

	void Connect(STRARR& cmd);
	void ConnectLocal(STRARR& cmd);
	void ConnectStatus(STRARR& cmd);
	void Send(STRARR& cmd);
	void Close(STRARR& cmd);

public:
	Client();
	virtual ~Client();
	virtual string GetModuleDesc(){ return "tcp client"; }
};

#endif
