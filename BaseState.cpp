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
#include "BaseState.h"

#include "SimpleJoy.h"

BaseState::BaseState()
{
    isPaused = false;
    firstPaused = false;
    nullify = false;
    needInit = true;
    nextState = 0;
	#ifndef PENJIN_ASCII
		input = NULL;
    #endif
}

BaseState::~BaseState()
{
    /// Tidy up
}

#ifndef PENJIN_ASCII
void BaseState::setSimpleJoy(SimpleJoy* sj)
{
    input = sj;
}
#endif

void BaseState::pauseUpdate()
{

}

#ifdef PENJIN_SDL
    void BaseState::pauseScreen(SDL_Surface* screen)
    {
        pauseSymbol(screen);
    }
    void BaseState::pauseSymbol(SDL_Surface* screen)
    {
        SDL_Rect pauseSymbol;
        pauseSymbol.x = pauseSymbol.y = 50;
        pauseSymbol.w = 50;
        pauseSymbol.h = 100;
        SDL_FillRect(screen, &pauseSymbol,SDL_MapRGB(screen->format, 96,96,96));

        pauseSymbol.x +=1;
        pauseSymbol.y +=1;
        pauseSymbol.h -=2;
        pauseSymbol.w -=2;
        SDL_FillRect(screen, &pauseSymbol,SDL_MapRGB(screen->format, 240,240,240));

        pauseSymbol.x +=88;
        pauseSymbol.y -=2;
        pauseSymbol.w +=2;
        pauseSymbol.h +=2;
        SDL_FillRect(screen, &pauseSymbol,SDL_MapRGB(screen->format, 96,96,96));

        pauseSymbol.x +=1;
        pauseSymbol.y +=1;
        pauseSymbol.h -=2;
        pauseSymbol.w -=2;
        SDL_FillRect(screen, &pauseSymbol,SDL_MapRGB(screen->format, 240,240,240));
    }
    void BaseState::render(SDL_Surface* screen)
    {
        // Clear screen
        GFX::clearScreen(screen);

        // Drawing commands here
        // update to screen performed automatically
    }
#else
    void BaseState::pauseScreen()
    {

    }
    void BaseState::pauseSymbol()
    {
    }
    void BaseState::render()
    {
        //	Clear Screen
        #ifndef PENJIN_ASCII
            GFX::clearScreen();
        #endif

/*
        //	Draw objects
        glBegin(GL_POLYGON);
            glVertex2f(xStart,yStart);
            glVertex2f(xStart,yStart+100.0f);
            glVertex2f(xStart+100.0f,yStart+100.0f);
            glVertex2f(xStart+100.0f,yStart);
        glEnd();
*/
        //	update to screen is performed automaticaly
    }
#endif
/*   */
void BaseState::update()
{
    // Perform physics ops here
}

void BaseState::unlimitedUpdate()
{

}

void BaseState::init()
{
    #if defined (PENJIN_GL) || defined (PENJIN_ES) || defined (PENJIN_ES2) || defined (PENJIN_SOFT)
        #ifdef PENJIN_3D
            GFX::init3DRendering();
        #else
            GFX::init2DRendering();
        #endif

	#else
        // Do any setup here
	#endif
}

void BaseState::userInput()
{

}

void BaseState::pauseInput()
{
    userInput();
}
