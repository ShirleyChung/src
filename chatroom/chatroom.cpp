#include "chatroom.h"

/* ��ѫǼҲժ�l�� */
ChatRoom::ChatRoom()
{
	this_type::AddFunc("showmembers", &ChatRoom::ShowMembers);
}

/* ��ܦ��� */
void ChatRoom::ShowMembers(STRARR& cmd)
{
	cout <<" not impl. yet.\n";
}
