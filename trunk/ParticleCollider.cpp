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
#include "ParticleCollider.h"

#include "Emitter.h"
#include "CollisionRegion.h"

ParticleCollider::ParticleCollider()
{
    //ctor
    region = NULL;
    region = new CollisionRegion;
    region->setWidth(1);
    region->setHeight(1);
}

ParticleCollider::~ParticleCollider()
{
    //dtor
    delete region;
}

void ParticleCollider::setPosition(const Vector2di& pos)
{
    region->setPosition(pos);
}

void ParticleCollider::setDimensions(const Vector2di& dims)
{
    region->setWidth(dims.x);
    region->setHeight(dims.y);
}

void ParticleCollider::linkEmitter(Emitter* e)
{
emit.push_back(e);
}

#ifdef PENJIN_SDL
void ParticleCollider::render(SDL_Surface* screen)
{
    region->render();
}
#else

void ParticleCollider::render()
{
#ifdef PENJIN_OGL

#endif
}
#endif
