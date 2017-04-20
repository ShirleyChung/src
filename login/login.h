#ifndef _login_module_for_login_users_save_db_2017_04
#define _login_module_for_login_users_save_db_2017_04

#include "../classes/funcdisp.hpp"
#include "../classes/singleton.hpp"

class Login:public FuncDisp<Login>
{
public:
	Login();
	virtual ~Login();
	
	string GetModuleDesc(){ return "Login Module"; }
};

#endif
