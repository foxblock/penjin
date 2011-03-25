/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

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
/***************************************************************************************************
*   \file RendererSDL_2d is a 2d renderer using SDL.
*   \author Kevin Winfield-Pantoja
*/

#ifndef RENDERERSDL_2D_H
#define RENDERERSDL_2D_H

#include "Renderer.h"

namespace Penjin
{
    class RendererSDL_2d : public Renderer
    {
        public:
            /** Default constructor */
            RendererSDL_2d();
            /** Default destructor */
            virtual ~RendererSDL_2d();

            virtual void showCursor(const bool& show);
            /** Sets the currently set width, height and bit-depth to the screen */
            virtual void applyVideoSettings();

            virtual void clear();
            virtual void blit();


            virtual void drawPixel(const Vector2d<float> & v);
            virtual void drawLine(const Vector2d<float> & p1, const Vector2d<float> & p2);
            virtual void drawRectangle(const Vector2d<float> & pos, const Vector2d<int> & dims);
            virtual void drawEllipse(const Vector2d<float> & centre, const float& rx, const float& ry);

            virtual void showVideoInfo();


        private:
            SDL_Surface* screen;
    };

typedef Singleton <RendererSDL_2d> GFX;
}
#endif // RENDERERSDL_2D_H
