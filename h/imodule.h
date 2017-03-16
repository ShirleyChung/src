#ifndef _module_interface_cpp
#define _module_interface_cpp

#include <list>
#include <string>

using namespace std;

class IModule
{
	vector<string> _apiList;
public:
	const vector<string>& GetAPIList() = 0;

};

#endif
