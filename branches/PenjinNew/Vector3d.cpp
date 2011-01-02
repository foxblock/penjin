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
#include "Vector3d.h"

bool Vector3d::operator== ( Vector3d& v )
{
	return (x==v.x && y==v.y && z==v.z);
}

Vector3d Vector3d::operator- ()
{
	return Vector3d(0-x,0-y,0-z);
}

const Vector3d& Vector3d::operator= ( const Vector3d& v )
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

const Vector3d& Vector3d::operator+= ( const Vector3d& v )
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

const Vector3d& Vector3d::operator-= ( const Vector3d& v )
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

const Vector3d& Vector3d::operator*= ( const float& s )
{
	x*=s;
	y*=s;
	z*=s;
	return *this;
}

const Vector3d& Vector3d::operator/= ( const float& s )
{
	x/=s;
	y/=s;
	z/=s;
	return *this;
}

const Vector3d Vector3d::operator+ ( const Vector3d& v ) const
{
	return Vector3d(x+v.x,y+v.y,z+v.z);
}

const Vector3d Vector3d::operator- ( const Vector3d& v ) const
{
	return Vector3d(x-v.x,y-v.y,z-v.z);
}

const Vector3d Vector3d::operator* ( const float& s ) const
{
	return Vector3d(x*s,y*s,z*s);
}

const Vector3d Vector3d::operator/ (double s) const
{
	return Vector3d(x/s,y/s,z/s);
}

const float Vector3d::dot( const Vector3d& v ) const
{
	return (x*v.x+y*v.y+z*v.z);
}

const float Vector3d::length() const
{
	return ( sqrt(x*x + y*y + z*z) );
}

const float Vector3d::lengthSquared() const
{
	return ( x*x + y*y + z*z );
}

const Vector3d Vector3d::unit() const
{
	float temp = length();
	return Vector3d(x/temp,y/temp,z/temp);
}

void Vector3d::normalise()
{
	float temp = length();
	if (temp >= 0.00001f)
	{
		x /= temp;
		y /= temp;
		z /= temp;
	}
	else
	{
		x = 0.0f;
		y = 1.0f;
		z = 0.0f;
	}
}

Vector3d Vector3d::normcrossprod(Vector3d v)
{
	Vector3d temp;
	temp = crossprod(v);
	return temp.unit();
}

Vector3d Vector3d::crossprod(Vector3d v)
{
	Vector3d temp;
	temp.x = y*v.z - z*v.y;
	temp.y = z*v.x - x*v.z;
	temp.z = x*v.y - y*v.x;
	return temp;
}

const Vector3d Vector3d::operator* ( float m[16] )
{
	Vector3d temp;

	temp.x = m[0]*this->x + m[4]*this->y + m[8]*this->z;
	temp.y = m[1]*this->x + m[5]*this->y + m[9]*this->z;
	temp.z = m[2]*this->x + m[6]*this->y + m[10]*this->z;

	return temp;
}

const Vector3d& Vector3d::operator*= ( float m[16] )
{
	Vector3d temp;

	temp.x = m[0]*this->x + m[4]*this->y + m[8]*this->z;
	temp.y = m[1]*this->x + m[5]*this->y + m[9]*this->z;
	temp.z = m[2]*this->x + m[6]*this->y + m[10]*this->z;

	*this = temp;

	return *this;
}

float* Vector3d::getVector()
{
	float* temp = new float[3];

	temp[0] = x;
	temp[1] = y;
	temp[2] = z;

	return temp;
}
