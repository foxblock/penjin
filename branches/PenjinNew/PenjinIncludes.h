/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
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
