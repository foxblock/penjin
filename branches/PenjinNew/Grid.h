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
#ifndef GRID_H
#define GRID_H

//  A simple class to draw gridlines in X and Z directions to help with spacial visualisation
#include "PenjinTypes.h"
#include "Colour.h"
#include <vector>

class Grid
{
    public:
        Grid();
        ~Grid();

        template <class T>
        void setOrigin(const T& o){origin.x = o.x; origin.y = o.y;}

        template <class T>
        void setNumTiles(const T& t){numTiles.x = t.x; numTiles.y = t.y;}

        void setColour(const Colour& c){colour = c;}

        void render();
        void refresh();

    private:
        Vector2di origin;       //  This is the nearest whole point where the gridlines will originate from
        Point2di numTiles;      //  This is the number of tiles in each direction to render
        Colour colour;
        vector <Point3di> lines;
};

#endif // GRID_H
