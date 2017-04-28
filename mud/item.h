#ifndef _items_intheworld_mud_for_item_description_and_actions_201704_
#define _items_intheworld_mud_for_item_description_and_actions_201704_

#include "mapdata.h"

class Item : public Object
{
	virtual void OnTimePass(time_t);
	
public:
	Item();
};

#endif