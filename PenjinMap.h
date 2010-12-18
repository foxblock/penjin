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
#ifndef PENJINMAP_H
#define PENJINMAP_H

#include "PenjinTypes.h"
#include "ErrorHandler.h"
class Parser;
class MapLayer;
#include <vector>


class PenjinMap
{
    public:
        /** Default constructor */
        PenjinMap();
        /** Default destructor */
        virtual ~PenjinMap();

        /** Renders the PenjinMap to the screen */
        void render();

        /** Update the PenjinMap */
        void update();
        void update(CRint xTile, CRint yTile);

        /** Set the TileMap's position
        *   \param xTile the horizontal tile to focus the map on.
        *   \param yTile the vertical tile to focus the map on
        */
        void setPosition(CRint xTile, CRint yTile);

        /** \brief Loads a Penjin map file
         *
         * \param fileName the file to be loaded.
         * \return the PENJIN_ERRORS error condition
         */
        PENJIN_ERRORS load(CRstring fileName);
        /** \brief Saves a Penjin map file to given location and file.
         *
         * \param fileName the file to be saved.
         * \return the PENJIN_ERRORS error condition
         */
        PENJIN_ERRORS save(CRstring fileName);

    private:
        Parser* parse;              /**< Parser object which parses the map file */
        vector <MapLayer*> layer;   /**< The vector of map layers */

        /** Copy constructor Disabled
         *  \param other Object to copy from
         */
        PenjinMap(const PenjinMap& other);
        /** Assignment operator Disabled
         *  \param other Object to assign from
         *  \return A reference to this
         */
        PenjinMap& operator=(const PenjinMap& other);
};

#endif // PENJINMAP_H
