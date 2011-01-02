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
#ifndef PARTICLEMIRROR_H
#define PARTICLEMIRROR_H

/*
    This class is to be used in conjunction with a particle Emitter class
    You grant this class access to the emitter and it will create a surface which will interect with
    that emitter's particles
*/
#include "ParticleCollider.h"

class ParticleMirror : public ParticleCollider
{
    public:
        ParticleMirror();
        virtual ~ParticleMirror();

        void setDampening(const Vector2di& d){dampening = d;}
        void setDampening(CRfloat d){dampening.x= dampening.y = d;}


        virtual void update();

    private:
        Vector2df dampening;
};

#endif // PARTICLEMIRROR_H
