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
*/#ifndef PENJINPOSITIONOBJECT_H
#define PENJINPOSITIONOBJECT_H

#include "PenjinObject.h"
#include "Vector2df.h"

class PenjinPositionObject : public PenjinObject
{
    public:
        /** Default constructor */
        PenjinPositionObject();
        /** Default destructor */
        virtual ~PenjinPositionObject();

        template <class T>
        void setPosition(const T& pos){position.x=pos.x;position.y=pos.y;}

        template <class T>
        void setPosition(const T& x, const T& y){position.x=x;position.y=y;}

        Vector2df getPosition()const;
    protected:
        Vector2df position;
    private:
};

#endif // PENJINPOSITIONOBJECT_H
