#ifndef _map_data_to_description_map_information_of_mud_world
#define _map_data_to_description_map_information_of_mud_world

#include <string>
#include <ctime>

using namespace std;

struct Object{

	virtual void OnTimePass(time_t) = 0;

};

struct Map
{
	string name;
	string desc;
};

#endif