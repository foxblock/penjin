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
#ifndef INC_AABB_H
#define INC_AABB_H

#include "PenjinTypes.h"
#include "Vector3d.h"
#include <list>
using namespace std;
#ifdef PENJIN3D
    #ifdef __linux__
        #include <SDL_opengl.h>
    #else
        #include <SDL/SDL_opengl.h>
    #endif
#endif

class AABB
{
	public :

		Vector3df centre;
		Vector3df halfLength;

		list<AABB*> subList;

        AABB();
        AABB(const float& xpos,const float& ypos,const float& zpos,const float& halfLength);
        AABB(const float& xpos,const float& ypos,const float& zpos,const float& xlen,const float& ylen,const float& zlen);
        ~AABB();

        void setAABB(const float& xpos,const float& ypos,const float& zpos,const float& halfLength);
        void setAABB(const float& xpos,const float& ypos,const float& zpos,const float& xlen,const float& ylen,const float& zlen);

        bool collided(const AABB& target, GLfloat rotMat[16]);
        void render(GLfloat rotMat[16]);

	private :
		Vector3df defCentre;
        void renderBox(const Vector3df& centre,const Vector3df& halfLength);
};

#endif
