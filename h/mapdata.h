#ifndef _map_data_to_description_map_information_of_mud_world
#define _map_data_to_description_map_information_of_mud_world

#include <string>
#include <ctime>
#include <map>

using namespace std;

#define MAPDATA "/MAPDATA"
#define AREADATA "/AREADATA"

struct Object{

	virtual void OnTimePass(time_t) = 0;

};

struct AbstractObject{
	virtual void OnTimePass(time_t){};
};

struct Place
{
	string name;
	string desc;
};

struct Size
{
	int width;
	int height;
	int depth;
};

struct Area: Place
{
	Size _size;
	map<string, AbstractObject> _items;
};

struct Map: Area
{
	map<string, Map> _entrance;
};

#endif