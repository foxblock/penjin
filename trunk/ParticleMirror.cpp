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
#include "ParticleMirror.h"
#include "Emitter.h"
#include "CollisionRegion.h"
ParticleMirror::ParticleMirror()
{
    //ctor
    //colour = RED;
    dampening.x=dampening.y=0.01f;
    //position.x = position.y = 0;
    //dimensions.x = dimensions.y = 1;
}

ParticleMirror::~ParticleMirror()
{
    //dtor
}

void ParticleMirror::update()
{
    for(int i = emit.size()-1; i >=0; --i)
    {
        if(emit[i])
        {
            for(int j = emit[i]->size()-1; j>=0; --j)
            {
                #ifdef PENJIN_3D
                    // TODO 3D version
                #else
                    // Check direction of particle
                    Vector2df v = emit[i]->getVelocity(j);
                    Vector2df pos = emit[i]->getPosition(j);
                    emit[i]->partCol->setPosition(pos);
                    SimpleDirection dir = emit[i]->partCol->directionTest(region,false);

                    if(dir != diNONE)
                    {
                        //collision
                        // Check particle velocity to guess which side is hit
                        emit[i]->setPosition(j,pos-v);
                        emit[i]->setAcceleration(j,Vector2df(0.0f,0.0f));
                        if((abs(v.x) <= 0.01f) || abs(v.y) <= 0.01f)
                        {
                            emit[i]->reset(j);
                            continue;
                        }
                        if(dir == diLEFT)
                            v.x = -abs(v.x * dampening.x);
                        else if(dir == diRIGHT)
                            v.x = abs(v.x * dampening.x);
                        if(dir == diTOP )
                            v.y = -abs(v.y * dampening.y);
                        else if( dir == diBOTTOM)
                            v.y = abs(v.y * dampening.y);
                        emit[i]->setVelocity(j,v);
                    }
                #endif
            }
        }
    }
}
