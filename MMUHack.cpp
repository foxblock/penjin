#include "MMUHack.h"

#ifdef PLATFORM_GP2X
MMUHack::MMUHack()
{
}

MMUHack::~MMUHack()
{
}


bool MMUHack::initHack()
{
	system("/sbin/rmmod mmuhack");
	system("/sbin/insmod mmuhack.o");

	int mmufd = open("/dev/mmuhack", O_RDWR);
	if(mmufd < 0)
	{
		printf("MMU hack failed");
		return false;
	}
	else
	{
		printf("MMU hack loaded");
		close(mmufd);
		return true;
	}
	return false;
}

void MMUHack::closeHack()
{
	system("/sbin/rmmod mmuhack");
}


void MMUHack::flushCache(void *start_address, void *end_address)
{
	flush_uppermem_cache(start_address, end_address, 0);
}
#endif   // GP2X
