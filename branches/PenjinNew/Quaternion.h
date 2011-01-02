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
#ifndef INC_QUATERNION_H
#define INC_QUATERNION_H

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include "Vector3d.h"
#include <SDL/SDL_opengl.h>
#include <cmath>

class Quaternion
{
	public :

		float s;		//Scalar component
		Vector3d v;		//Vector component

	/* Constructors */
        Quaternion();
        Quaternion(const float& w,const float& x,const float& y,const float& z);
        Quaternion(const float& roll,const float& pitch,const float& yaw);

	/* Operators */
        Quaternion operator=(const Quaternion& q);
        Quaternion operator*(const Quaternion& q);
        Quaternion operator~();

	/* Functions to Create Quaternions */
        Quaternion createFromEuler(float roll, float pitch, float yaw);

	/* Functions to Convert Quaternions */
        Vector3d convertToEuler();
        void convertToMatrix(GLfloat m[16]);

        Quaternion Slerp(const Quaternion& current,const Quaternion& target,const float& t);
};
#endif
