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
#ifndef BACKBUFFER_H
#define BACKBUFFER_H
#include "GFX.h"
#include "Pixel.h"

class BackBuffer
{
    public:
        BackBuffer();
        #ifdef PENJIN_SDL
            BackBuffer(SDL_Surface* src);   //  create backbuffer from src surface
        #endif
        ~BackBuffer();

        #ifdef PENJIN_SDL
            void render(SDL_Surface* screen);    // Render to specific surface
            void render(){render(screen);}       // Render to the screen
            void update(SDL_Surface* screen);    // Update from specific surface
            void update(){update(screen);}       // Update from screen contents
            void setAlpha(CRuchar alpha){SDL_SetAlpha(buffer, SDL_SRCALPHA, alpha);}
            void setPixel(Pixel p){p.render(buffer);}
        #else
            void render();
            void update(){;}
            void setAlpha(CRuchar a){alpha = a * 0.003921569f;}
            void setAlpha(CRfloat a){alpha = a;}
        #endif



    private:
        #ifdef PENJIN_SDL
            SDL_Surface* buffer;    //  The back buffer
            SDL_Surface* screen;    //  The pointer to the screen.
        #else
            float alpha;
        #endif
};

#endif // BACKBUFFER_H
