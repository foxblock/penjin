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
#ifndef MAPLAYER_H
#define MAPLAYER_H

#include <vector>
using std::vector;
#include "DoubleVector.h"
class PenjinTile;

class MapLayer
{
    public:
        /** Default constructor */
        MapLayer();
        /** Default destructor */
        virtual ~MapLayer();

        void render();
        void update();

    private:
        DoubleVector <int>  data;   //  Stores the tile idices for the map [x][y]
        vector<PenjinTile*>  tiles; // stores the actual tile image data for this layer
        float parallaxMult; /**< The value used for parallax scrolling in this layer*/
        Vector2df offset;       //  This is the value that determines which part of the map falls in the cameras viewing area.
        Vector2di tileDims;     //  The dimensions that each tile must have in this layer
        Vector2di mapDims;      //  Total dimensions of the mapLayer

        /** Copy constructor
         *  \param other Object to copy from
         */

        MapLayer(const MapLayer& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        MapLayer& operator=(const MapLayer& other);
};

#endif // MAPLAYER_H
