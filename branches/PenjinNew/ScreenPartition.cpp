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
#include "ScreenPartition.h"

ScreenPartition::ScreenPartition()
{
	//	TOP_LEFT
	setPartition(Vector2di(160,120));
}

ScreenPartition::~ScreenPartition()
{
}

uint ScreenPartition::getPartition(CRint x,CRint y)
{
	//	Work out if the point is on the left or right of the screen first
	if(x < midPoint.x)
	{
		//	Left hand side of screen
		//	Now check if it is up or down
		if(y < midPoint.y)
			return TOP_LEFT;

		return BOTTOM_LEFT;
	}
	else
	{
		//	Right hand side of screen
		//	Now check if it is up or down
		if(y > midPoint.y)
			return BOTTOM_RIGHT;

		return TOP_RIGHT;
	}
}

uint ScreenPartition::getPartition(const Vector2di& position)
{
	return getPartition(position.x,position.y);
}

void ScreenPartition::setPartition(const Vector2di& midPoint)
{
	this->midPoint = midPoint;
}
