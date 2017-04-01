#ifndef _tcpclient_module_for_listening_request_support_icommodule_2017
#define _tcpclient_module_for_listening_request_support_icommodule_2017

#include "../classes/funcdisp.h"
#include "../classes/tcpclient.h"

class Client: public FuncDisp<Client>, public TCPClient
{
	static Client* _inst;

	void Connect(STRARR& cmd);
	void Send(STRARR& cmd);

	Client();
public:
	static Client* GetModuleInst(){ if (!_inst) { _inst = new Client(); return _inst; } else return _inst; };	
	
	
	virtual string GetModuleDesc(){ return "tcp client"; }
	
};

#endif