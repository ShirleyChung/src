#ifndef _chat_room_socket_application_2017_04_sly_
#define _chat_room_socket_application_2017_04_sly_

#include "../server/server.h"

class ChatRoom: public Server, public FuncDisp<ChatRoom>
{
	typedef FuncDisp<ChatRoom> this_type;

protected:
	void ShowMembers(STRARR& cmd);

public:
	ChatRoom();
	virtual ~ChatRoom(){};
	
	virtual void OnConnect(string ip, int sck){};
};

#endif
