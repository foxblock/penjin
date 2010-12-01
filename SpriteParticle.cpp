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
#include "SpriteParticle.h"

SpriteParticle::SpriteParticle()
{
    //ctor
    particleType = SPRITE_PARTICLE;
    spritePointer = NULL;
    alpha = 255;
    colour.setAlpha(alpha);
}

SpriteParticle::~SpriteParticle()
{
    //dtor
}

#ifdef PENJIN_SDL
    void SpriteParticle::render(SDL_Surface* screen)
    {
        spritePointer->setAlpha(alpha);
        #ifdef PENJIN_FIXED
            spritePointer->setPosition(Vector2di(position.x.intValue >> 16, position.y.intValue >> 16));
        #else
            spritePointer->setPosition(Vector2di(position.x, position.y));
        #endif
        spritePointer->render(screen);
    }
#else
    void SpriteParticle::render()
    {
        spritePointer->setPosition(position);
        spritePointer->render();
    }
#endif


void SpriteParticle::changeAlpha(CRfloat value)
{
    #ifdef PENJIN_FIXED
        alpha = fixedpoint::fix2int(alpha - value);
    #else
        alpha-=value;
    #endif
}
