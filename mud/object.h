#ifndef _object_interface_for_interaction_with_map_2017_04_time_desc_pose_etc_
#define _object_interface_for_interaction_with_map_2017_04_time_desc_pose_etc_

#include <ctime>

struct Object{

	virtual void OnTimePass(time_t) = 0;

};

#endif