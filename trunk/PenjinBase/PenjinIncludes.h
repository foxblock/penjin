#ifndef INCLUDES_H
#define INCLUDES_H

#ifdef PLATFORM_WII
    #include <gccore.h>
#endif
#include <SDL/SDL.h>
#ifdef PENJIN_GL
    #include <SDL/SDL_opengl.h>
#endif

#include "version.h"    //  Application version info
#include "ErrorHandler.h"	// Will report various errors depending on where called.
#include "GFX.h"
#include "SimpleJoy.h"

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#include "Timer.h"			//	Game timing class.

#endif	//	INCLUDES_H
