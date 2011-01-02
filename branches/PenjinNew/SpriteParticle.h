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
#ifndef SPRITEPARTICLE_H
#define SPRITEPARTICLE_H

#include "Particle.h"
#include "Sprite.h"

class SpriteParticle : public Particle
{
    public:
        SpriteParticle();
        SpriteParticle(SpriteParticle& spr){*this = spr;}
        //SpriteParticle(Particle& part){*this = part;}
        virtual ~SpriteParticle();

        ///  WARNING THE EMITTER HANDLES SCREEN LOCKING AND UNLOCKING IN SDL!
        #ifdef PENJIN_SDL
            virtual void render(SDL_Surface* screen);
        #else
            virtual void render();
        #endif
        virtual void changeAlpha(CRfloat value);
        virtual void setAlpha(CRuchar a){alpha = a;}
        void setSprite(Sprite* sprite){spritePointer = sprite;}

    private:
        Sprite* spritePointer;
        uint alpha;
};

#endif // SPRITEPARTICLE_H
