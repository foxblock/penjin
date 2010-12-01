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
#include "AnimatedParticle.h"

AnimatedParticle::AnimatedParticle()
{
    //ctor
    particleType = ANIMATED_PARTICLE;
    spritePointer = NULL;
}

AnimatedParticle::~AnimatedParticle()
{
    //dtor
}

#ifdef PENJIN_SDL
    void AnimatedParticle::render(SDL_Surface* screen)
    {
        #ifdef PENJIN_FIXED
            spritePointer->setPosition(Vector2di(position.x.intValue >> 16, position.y.intValue >> 16));
        #else
            spritePointer->setPosition(Vector2di(position.x, position.y));
        #endif
        spritePointer->render(screen);
    }
#else
    void AnimatedParticle::render()
    {
        spritePointer->setPosition(position);
        spritePointer->render();
    }
#endif


void AnimatedParticle::changeAlpha(CRuchar value)
{
    spritePointer->setAlpha(spritePointer->getAlpha() + value);
}

void AnimatedParticle::update()
{
    spritePointer->update();
    ++lifeTime;

    //  Update position of particle
    position = position + velocity;

    //  Apply acceleration and gravity
    velocity += acceleration;
    acceleration += gravity;


    if(useDeviance)
        #ifndef PENJIN_3D
            #ifdef PENJIN_FIXED
                position = position + Vector2dx(Random::nextFixed()-deviation,Random::nextFixed()-deviation);
            #else
                position = position + Vector2df(Random::nextFloat()-deviation,Random::nextFloat()-deviation);
            #endif
        #else
            position = position + Vector3df(Random::nextFloat()-deviation,Random::nextFloat()-deviation,Random::nextFloat()-deviation);
        #endif

}
