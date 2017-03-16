#ifndef _loader_for_modules_funcationlities_2017_03
#define _loader_for_modules_funcationlities_2017_03

#include <string>

using namespace std;

class Loader
{

public:
	Loader();
	virtual ~Loader();

	bool Load(string file);
};

#endif
