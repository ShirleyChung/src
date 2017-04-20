#include "login.h"

extern "C" IModule* GetModule()
{
	return Singleton<Login>::GetInstance();
}

Login::Login()
{
	_name = "Login";
}

Login::~Login()
{
}
