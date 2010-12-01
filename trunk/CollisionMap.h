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
#ifndef COLLISIONMAP_H
#define COLLISIONMAP_H

#include "Image.h"
#include "GFX.h"

class CollisionMap
{
    public:
        CollisionMap();
        ~CollisionMap();

        PENJIN_ERRORS loadImage(CRstring image){return map.loadImageNoKey(image);}
        void setNoCollisionColour(const Colour& c){noCollision = c;}
        Colour getNoCollisionColour()const{return noCollision;}

        #ifdef PENJIN_SDL
            void render(SDL_Surface* screen);
            void render();
        #else
            void render();
        #endif

        Colour getCollisionType(CRuint x, CRuint y)
		{
			if(x < 0 || y < 0 || x > map.getWidth() || y > map.getHeight())
				return noCollision;

			Colour c = map.getPixel(x,y);
			#ifdef PENJIN_SDL
                c.alpha = 255;
            #else
                c.alpha = 1.0f;
            #endif

			return c;
		}  //  check what sort of collision has been made.

bool hasCollided(CRuint x, CRuint y){return (getCollisionType(x,y) != noCollision);}         //  has there been a collision?

    private:
        Image map;
        Colour noCollision;
};

#endif // COLLISIONMAP_H
