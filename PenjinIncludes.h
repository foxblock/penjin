#ifndef INCLUDES_H
#define INCLUDES_H

#include "Penjin.h"

#ifdef PLATFORM_WII
    #include <gccore.h>
#endif

#ifdef PENJIN_SOFT
    /// Setup SW Renderer
    #include "trenki/renderer/geometry_processor.h"
    #include "trenki/renderer/rasterizer_subdivaffine.h"
    #include "trenki/renderer/span.h"
    using namespace swr;
#endif

#ifdef PENJIN_SDL
    #include <SDL/SDL.h>
#elif PENJIN_GL
    #include <SDL/SDL_opengl.h>
#elif PENJIN_CACA
    #include <cucul.h>
    #include <caca.h>
#elif PENJIN_ASCII
    #include <ncurses.h>
#endif

#include "version.h"    //  Application version info
#include "ErrorHandler.h"	// Will report various errors depending on where called.

#ifndef PENJIN_ASCII
    #include "GFX.h"
    #include "SimpleJoy.h"
#endif

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#include "Timer.h"			//	Game timing class.

#endif	//	INCLUDES_H
