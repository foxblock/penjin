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
#include "Vector3df.h"

Vector3df::Vector3df()
{
    //ctor
}

void Vector3df::normalise()
{
    float temp = 1/length();
	if (temp <= std::numeric_limits<float>::max())
	{
		x *= temp;
		y *= temp;
		z *= temp;
	}
	else
	{
		x = 0.0f;
		y = 1.0f;
		z = 0.0f;
	}
}

Vector3df Vector3df::cross(const Vector3df& v)
{
	Vector3df temp;
	temp.x = y*v.z - z*v.y;
	temp.y = z*v.x - x*v.z;
	temp.z = x*v.y - y*v.x;
	return temp;
}

Vector3df Vector3df::normalisedCross(const Vector3df& v)
{
    Vector3df out = cross(v);
    out.normalise();
    return out;
}
