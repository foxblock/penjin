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
#include "BackBuffer.h"

BackBuffer::BackBuffer()
{
    //ctor
    #ifdef PENJIN_SDL
        buffer = NULL;
        screen = GFX::getVideoSurface();
    #else
        #ifdef PENJIN_GL
            glClear(GL_ACCUM_BUFFER_BIT);
        #endif
        alpha = 1.0f;
    #endif
}

BackBuffer::~BackBuffer()
{
    //dtor
    #ifdef PENJIN_SDL
        if(buffer)
            SDL_FreeSurface(buffer);
        buffer = NULL;
    #endif
}

#ifdef PENJIN_SDL
    void BackBuffer::render(SDL_Surface* scr)
    {
        SDL_BlitSurface(buffer, NULL, scr, NULL);
    }

    void BackBuffer::update(SDL_Surface* scr)
    {
        if(buffer == NULL)
            buffer = SDL_CreateRGBSurface(screen->flags,scr->w, scr->h, screen->format->BitsPerPixel, 0, 0, 0, 0);
        SDL_BlitSurface(scr, NULL, buffer, NULL);
    }
#else
    void BackBuffer::render()
    {
        #ifdef PENJIN_GL
        glAccum(GL_MULT, alpha);
        glAccum(GL_ACCUM, 1.0f-alpha);
        glAccum(GL_RETURN, 1.0f);
        #endif
    }
#endif
