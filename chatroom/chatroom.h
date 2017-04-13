#ifndef _chat_room_socket_application_2017_04_sly_
#define _chat_room_socket_application_2017_04_sly_

#include "../classes/tcpserver.h"

class ChatRoom: public TCPServer
{
public:
	ChatRoom(){};
	
	virtual void OnConnect(string ip, int sck){};
};

#endif
