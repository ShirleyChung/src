#ifndef _tcpclient_module_for_listening_request_support_icommodule_2017
#define _tcpclient_module_for_listening_request_support_icommodule_2017

#include "../classes/funcdisp.hpp"
#include "../classes/tcpclient.h"
#include "../classes/singleton.hpp"

class Client: public FuncDisp<Client>, public TCPClient
{
	void Connect(STRARR& cmd);
	void Send(STRARR& cmd);

public:
	Client();
	virtual ~Client();
	virtual string GetModuleDesc(){ return "tcp client"; }
};

#endif
