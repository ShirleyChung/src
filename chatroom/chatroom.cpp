#include "chatroom.h"

/* 聊天室模組初始化 */
ChatRoom::ChatRoom()
{
	this_type::AddFunc("showmembers", &ChatRoom::ShowMembers);
}

/* 顯示成員 */
void ChatRoom::ShowMembers(STRARR& cmd)
{
	cout <<" not impl. yet.\n";
}
