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
#include "Vector2dx.h"

Vector2dx::Vector2dx()
{
    //ctor
}

void Vector2dx::normalise()
{
    fixed_point<16> temp = 1/length();
	if (temp <= std::numeric_limits<float>::max())
	{
		x *= temp;
		y *= temp;
	}
	else
	{
		x = 0;
		y = 1;
	}
}
