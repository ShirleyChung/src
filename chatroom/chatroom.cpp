#include "chatroom.h"

ChatRoom::ChatRoom()
{
	this_type::AddFunc("showmembers", &ChatRoom::ShowMembers);
}

void ChatRoom::ShowMembers(STRARR& cmd)
{
	cout <<" not impl. yet.\n";
}
