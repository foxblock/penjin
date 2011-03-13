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
*/#ifndef RENDERER_H
#define RENDERER_H

#include "DimensionObject.h"
#include "Singleton.h"
#include "ColourObject.h"


namespace Penjin
{
    class Renderer : public DimensionObject
    {
        public:
            /** Default constructor */
            Renderer();
            /** Default destructor */
            virtual ~Renderer();

            void setBitsPerPixel(const int& bpp);
            void setFullscreen(const bool& fs);
            void setClearColour(const Colour& c);

            virtual void showCursor(const bool& show)=0;
            /** Sets the currently set width, height and bit-depth to the screen */
            virtual void applyVideoSettings()=0;

            virtual void clear()=0;
            virtual void blit()=0;


            virtual void drawPixel(const Vector2d<float> & v, Colour c)=0;
            virtual void drawLine(const Vector2d<float> & p1, const Vector2d<float> & p2)=0;
            virtual void drawRectangle(const Vector2d<float> & pos, const Vector2d<int> & dims, const Colour& c, const int& lineWidth)=0;
            virtual void drawEllipse(const Vector2d<float> & centre, const float& rx, const float& ry, const Colour& c, const int& lineWdith)=0;

            virtual void showVideoInfo()=0;

        protected:
            int bpp;
            bool fullScreen;
            Colour clearColour;
    };
}
#endif // RENDERER_H
