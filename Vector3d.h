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
#ifndef INC_VECTOR3D_H
#define INC_VECTOR3D_H

#include <cmath>
#ifdef PENJIN_3D
#include <SDL/SDL_opengl.h>
#endif
#include "PenjinTypes.h"

class Vector3d
{
	public:
		float x, y, z;

	Vector3d()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	Vector3d(const float& x,const float& y,const float& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
    Vector3d(const Vector3df& vec)
    {
        this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
    }
	bool operator== ( Vector3d& v );
	Vector3d operator- ();
	const Vector3d& operator= ( const Vector3d& v );
	const Vector3d& operator= ( const Vector3df& v );
	const Vector3d& operator+= ( const Vector3d& v );
	const Vector3d& operator-= ( const Vector3d& v );
	const Vector3d& operator*= ( const float& s );
	const Vector3d& operator/= ( const float& s );
	const Vector3d operator+ ( const Vector3d& v ) const;
	const Vector3d operator- ( const Vector3d& v ) const;
	const Vector3d operator* ( const float& s ) const;
	const Vector3d operator/ (double s) const;
	const float dot( const Vector3d& v ) const;
	const float length() const;
	const float lengthSquared() const;
	const Vector3d unit() const;
	void normalise();

	friend inline const Vector3d operator* ( const float& s, const Vector3d& v )
	{
		return v*s;
	}

	Vector3d normcrossprod(Vector3d v);
	Vector3d crossprod(Vector3d v);

	const Vector3d operator* ( float m[16] );
	const Vector3d& operator*= ( float m[16] );

	float* getVector();
	Vector3df getVector3df(){return Vector3df(x,y,z);}
};

#endif
