#include "../shareclass/daemon.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (!initDaemon())
	{	
		printf("setup daemon fail!\n");
	}
	else
	{
		char msg[128] = "";
		int tick = 0;
		while(true)
		{	
			sprintf(msg, "[%d]tick.", tick++);
			writeLog("test", msg);
			sleep(5);
		}
	}
	return 0;	
}
