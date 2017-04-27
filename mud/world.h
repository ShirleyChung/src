#ifndef _world_clas_for_mud_game_world_information_and_map_2017_04
#define _world_clas_for_mud_game_world_information_and_map_2017_04

#include "../classes/thread.hpp"
#include "../classes/configfile.h"
#include "../classes/tool.h"
#include "../h/mapdata.h"

class World : public Thread
{
	ConfigFile _conf;
	time_t _world_time;
	
	void TimePassing(time_t);
	
	bool _run;
	int  _period;
public:
	World();
	
	void run();
};

#endif