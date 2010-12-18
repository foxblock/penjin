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
#ifndef PENJINTILE_H
#define PENJINTILE_H
/**
*   \author Kevin Winfield-Pantoja
*   A PenjinTile is a renderable object with additional collision info etc
*/
#include "DisplayEntity.h"

class PenjinTile : public DisplayEntity
{
    public:
        /** Default constructor */
        PenjinTile();
        /** Default destructor */
        virtual ~PenjinTile();


    private:

        /** Copy constructor
         *  \param other Object to copy from
         */
        PenjinTile(const PenjinTile& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        PenjinTile& operator=(const PenjinTile& other);
};

#endif // PENJINTILE_H
