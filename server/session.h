#ifndef _session_define_for_server_connect_application_201704_
#define _session_define_for_server_connect_application_201704_

#include <sys/socket.h>
#include <sys/poll.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "thread.hpp"
#include "tool.h"

using namespace std;

typedef void(*SESCALLBACK)(string,int, int, void*);

class Session : public Thread
{
	int sck;
	string ip;
	bool _run;

	void* _pt;
	int _bufsize;
	
	SESCALLBACK _cb;

public:	
	enum _CBSIGNAL{ ENDSES, NEWMSG };

	Session(int sck, const string& ip, void* pt):sck(sck), ip(ip), _pt(pt), _run(true), _bufsize(1024){};
	virtual ~Session(){ close(sck); }
	
	void SetBufSize(int sz){ _bufsize = sz; }
	void SetCallback(SESCALLBACK cb, void* pt){ _cb = cb; _pt = pt; }
	
	// Thread
	virtual void run();

	void ShowInfo(){
		cout<<"socket:"<<sck<<"\n\tIP:"<<ip<<"\n\trunning:"<<_run<<'\n';
	}
};

#endif