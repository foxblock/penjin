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
#ifndef SCREENPARTITION_H
#define SCREENPARTITION_H

#include "PenjinTypes.h"

/*
ABOUT:  Takes a screen, splitting it into quadrants
        This can be used to sort game objects, to minimise collision checks
*/

enum partitions
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	UNKNOWN_PARTITION
};

class ScreenPartition
{
    public:
        ScreenPartition();
        ~ScreenPartition();

        //	Set the middle of the screen
        void setPartition(const Vector2di& midPoint);

        //	check which partition the position is in
        uint getPartition(const Vector2di& position);
        uint getPartition(CRint x,CRint y);
        //uint getPartition(const Vector2df& position){return getPartition(position.x.intValue >> 16,position.y.intValue >> 16);};
    private:
        Vector2di midPoint;
};
#endif	//	SCREENPARTITION_H

