#ifndef MMUHACK_H
#define MMUHACK_H

#ifdef PLATFORM_GP2X
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/mman.h>


#include "mmuhack/flush_uppermem_cache.h"


class MMUHack
{
    public:
        bool initHack();	//	Startup the MMU Hack. should be done after any dispay initialisation
        void closeHack();	//	Shitdown the MMU Hack. performed before program shutdown

        //	Flush cache clears cache and should be called immediately before you blit the screen
        //e.g. fr SDL:  hack.flushCache(screen->pixels, screen->pixels + 76800)//320*240 = 76800
        void flushCache(void *start_address, void *end_address);
        MMUHack();
        ~MMUHack();
};
#endif   // GP2X
#endif	//	MMUHACK_H
