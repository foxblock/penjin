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
#include "Sprite.h"

Sprite::Sprite()
{
    position.x = 0;
    position.y = 0;
    #ifdef PENJIN_3D
        position.z = 0.0f;
    #endif
    #ifdef PENJIN_SDL
        screen = GFX::getVideoSurface();
    #endif
}
#ifndef PENJIN_3D
    Sprite::Sprite(CRint x,CRint y)
    {
        setPosition(x,y);
        #ifdef PENJIN_SDL
            screen = GFX::getVideoSurface();
        #endif
    }
#else
    Sprite::Sprite(CRfloat x,CRfloat y)
    {
        setPosition(x,y);
    }
    Sprite::Sprite(CRfloat x,CRfloat y,CRfloat z)
    {
        setPosition(x,y,z);
    }
    Sprite::Sprite(const Vector3df& position)
    {
        setPosition(position);
    }
    Sprite::Sprite(const Vector2df& position)
    {
        setPosition(position);
    }
#endif

#ifdef PENJIN_SDL
PENJIN_ERRORS Sprite::loadSprite(SDL_Surface* s)
{
    image.loadImage(s);
    image.setSurfaceSharing(true,image.size()-1);
    return PENJIN_OK;
}
#endif

PENJIN_ERRORS Sprite::loadSprite(CRstring fileName){return image.loadImage(fileName);}

#ifdef PENJIN_SDL
    void Sprite::render(SDL_Surface* screen){image.renderImage(screen,position);}
#else
    void Sprite::render(){image.renderImage(position);}
#endif

#ifdef PENJIN_SDL
bool Sprite::hasCollided(Sprite &spr)
{/*
   uint a = image.getWidth()/2;
   uint b = spr.image.getWidth()/2;

   IntVector2d temp = *this - IntVector2d(spr.getX(),spr.getY());

	if (temp.lengthSquared() <= a * a + b * b)
	 	return true;
*/
	return false;
}
#endif
