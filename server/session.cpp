#include "session.h"

void Session::run()
{
	cout<<"=>start waiting input..\n ";

	string msg;
	
	while(_run)
	{
		pollfd fd = {sck, POLLIN, 0};
		if ( 0 >= poll(&fd, 1, 1000) ) continue;
		if (fd.revents & (POLLERR|POLLHUP|POLLNVAL)) break;
		cout<<"reading "<<sck<<"...";
		string buf(_bufsize, 0);
		int n = read(sck, (char*)&(*buf.begin()), _bufsize); //blocked here..
		if (!n) break;
		cout<<" read.\n";
		rtrim( buf, string(1,0) );
		msg += buf;
		cout<<"msg:"<<msg<<"\n";
		if (n < _bufsize)
		{
			if (_cb) _cb(msg, sck, NEWMSG, _pt);
			msg.clear();
		}
	}
	cout<<"=>end ssesion\n";
	
	if(_cb) _cb(msg, sck, ENDSES, _pt);
}