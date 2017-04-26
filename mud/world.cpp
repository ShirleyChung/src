#include "world.h"
#include <unistd.h>

World::World()
:_conf("./conf/world.cfg")
,_run(true)
,_period(1500)
{
}

void World::TimePassing(time_t)
{
	//notify time to objects..
}

void World::run()
{
	while(_run)
	{
		TimePassing(_world_time++);
		usleep(_period);
	}
}