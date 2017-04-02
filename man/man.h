#ifndef _manual_help_2017_module
#define _manual_help_2017_module

#include "../classes/funcdisp.hpp"

using namespace std;

class Man: public FuncDisp<Man>
{
	static Man* _inst;
	
	void Help(STRARR&);

	void Manual(STRARR&);
	
	string _desc;
	
public:
	Man();
	virtual string GetModuleDesc(){ return _desc; }

	static IModule* GetModule(){
		return (_inst)? _inst: new Man();
	}
};

#endif
