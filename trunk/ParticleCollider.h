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
#ifndef PARTICLECOLLIDER_H
#define PARTICLECOLLIDER_H

/*
This is a base class for the Penjin Particle system which describes a collidable object
to interact with the Particles.

You can create sub classes from this to allow different interactions.
e.g. a simple class which reflects upon collision
another which kills and resets the particles.

Author Kevin Winfield-Pantoja
*/
#include "Emitter.h"

class ParticleCollider
{

    public:
        ParticleCollider();
        virtual ~ParticleCollider();

        void linkEmitter(Emitter* e){emit.push_back(e);}
        void setPosition(const Vector2di& position){this->position = position;}
        void setDimensions(const Vector2di& dims){dimensions = dims;}
        void setColour(const Colour& c){colour = c;}

        virtual void update(){;}
    #ifdef PENJIN_SDL
        void render(SDL_Surface* screen);
    #else
        void render();
    #endif

    protected:
        vector <Emitter*> emit; // These are just pointers, we manipulate already existing particles
        Vector2di position;
        Vector2di dimensions;
        Colour colour;
};

#endif // PARTICLECOLLIDER_H
