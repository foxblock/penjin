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

ParticleCollider::ParticleCollider()
{
    //ctor
    colour = RED;
    position.x = position.y = 0;
    dimensions.x = dimensions.y = 1;
}

ParticleCollider::~ParticleCollider()
{
    //dtor
}

#ifdef PENJIN_SDL
void ParticleCollider::render(SDL_Surface* screen)
{
    SDL_Rect t;
    t.x = position.x;
    t.y = position.y;
    t.w = dimensions.x;
    t.h = dimensions.y;
    SDL_FillRect(screen, &t, SDL_MapRGB(screen->format,colour.red,colour.green,colour.blue));
}
#else

void ParticleCollider::render()
{
#ifdef PENJIN_OGL

#endif
}
#endif
