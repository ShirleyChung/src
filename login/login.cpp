#include "login.h"

extern "C" IModule* GetModule()
{
	return Singleton<Login>::GetInstance();
}

Login::Login()
{

}

Login::~Login()
{
}
