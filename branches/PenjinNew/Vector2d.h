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
*/#ifndef VECTOR2DI_H
#define VECTOR2DI_H

#include "Vector1d.h"
namespace Penjin
{
    template <typename T>
    class Vector2d : public Vector1d<T>
    {
        public:
            /** Default constructor */
            Vector2d();
            Vector2d(const T& x, const T& y);
            Vector2d(const Vector1d<T> & v);
            Vector2d(const Vector2d<T> & v);

            /** Default destructor */
            virtual ~Vector2d();

            void setY(const T& v){y=v;}

            int getY()const;

            virtual float dot(const T& v)const;

            virtual float length()const;
            virtual float lengthSquared()const;
            virtual Vector2d<T> unit();
            virtual void normalise();

            virtual bool equals(const Vector1d<T>& v);
            virtual bool equals(const T& v);

        T y;
    };
}

#endif // VECTOR2DI_H
