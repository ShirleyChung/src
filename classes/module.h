#ifndef _module_interface_cpp
#define _module_interface_cpp

#include <vector>
#include <string>

using namespace std;

template<class T>
class Module
{
protected:
	static Module<T>*	_inst;
	vector<string> 	_apiList;

	Module(){}
	virtual ~Module(){ 
		if (_inst) delete _inst;
	}
public:
	const vector<string>& GetAPIList(){ return _apiList; }

	static Module<T>* GetModule()
	{
		return (_inst)? _inst: (_inst = new Module<T>);
	}
};

#endif
