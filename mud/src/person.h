#ifndef _person_intheworld_as_a_character_or_npc_interact_with_others_or_item_and_move_2017_04
#define _person_intheworld_as_a_character_or_npc_interact_with_others_or_item_and_move_2017_04

#include "mapdata.h"

class Person: public Object
{
	virtual void OnTimePass(time_t);
	
public:
	Person();
	virtual ~Person();
};

#endif