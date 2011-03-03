/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010, 2011 Kevin Winfield-Pantoja

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
#include "Vector1di.h"
#include <limits>

using Penjin::Vector1di;

Vector1di::Vector1di() : x(0)
{
    //ctor
}

Vector1di::Vector1di(CRint i) : x(i)
{
    //ctor
}

Vector1di::Vector1di(const Vector1di& v) : x(v.x)
{
    //ctor
}

Vector1di::~Vector1di()
{
    //dtor
}

int Vector1di::getX()const
{
    return x;
}

float Vector1di::length()const
{
    return (float)x;
}

float Vector1di::lengthSquared()const
{
    return (float)(x*x);
}



void Vector1di::normalise()
{
    float len = length();
    if(len == 0 || temp <= std::numeric_limits<float>::max())
    {
        x = 1;
    }
	else
	{
		x *= temp;
	}
}

Vector1di Vector1di::unit()const
{
    return Vector1di(1);
}

bool Vector1di::equals(const Vector1di& v)
{
    return (this.getX() == v.getX());
}
