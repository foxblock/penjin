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
*/#ifndef DIMENSIONOBJECT_H
#define DIMENSIONOBJECT_H
#include "Object.h"
#include "Vector2d.h"

using Penjin::Object;
using Penjin::Vector2d;

/**
    \brief A class that describes the width and height of an object.
*/

namespace Penjin
{
    class DimensionObject : public Object
    {
        public:
            /** Default constructor */
            DimensionObject();
            /** Default destructor */
            virtual ~DimensionObject();

            // Setting methods
            template <class T>
            void setDimensions(const T& dims){dimensions.x=dims.x;dimensions.y=dims.y;}
            template <class T>
            void setWidth(const T& w){dimensions.x=w;}
            template <class T>
            void setHeight(const T& h){dimensions.y=h;}

            // Getting methods
            Vector2d<int> getDimensions()const;
            int getWidth()const;
            int getHeight()const;

        protected:
            Vector2d<int> dimensions;
    };
}
#endif // DIMENSIONOBJECT_H
