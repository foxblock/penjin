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
#ifndef LINE_H
#define LINE_H

#include "PenjinTypes.h"
#include "Colour.h"
#ifdef PENJIN_GL
#include <SDL/SDL_opengl.h>
#elif PENJIN_ES || PENJIN_ES2
    #include <GLES/gl.h>
    #include <GLES/egl.h>
#elif PENJIN_SDL
#include <SDL/SDL_gfxPrimitives.h>
#endif
class Line
{
    public:
        Line();

        virtual ~Line();

        template <class T>
        void setStartPosition(const T& pos){start.x = pos.x;start.y=pos.y;}
        template <class T>
        void setEndPosition(const T& pos){end.x = pos.x;end.y=pos.y;}

        void setColour(const Colour& c){colour = c;}
        void setLineWidth(CRfloat w){lineWidth = w;}

        #ifdef PENJIN_SDL
            void render(SDL_Surface* screen);
        #endif
        void render();

    private:
        #ifdef PENJIN_3D
            Point3di start;
            Point3di end;
        #else
            Point2di start;
            Point2di end;
        #endif
        float lineWidth;
        Colour colour;
        #ifdef PENJIN_SDL
        SDL_Surface* screen;
        #endif
};

#endif // LINE_H
