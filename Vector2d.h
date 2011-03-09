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
#include <cmath>
namespace Penjin
{
    template <typename T>
    class Vector2d : public Vector1d<T>
    {
        public:
            /** Default constructor */
            Vector2d() : y(0){;}
            Vector2d(const T& x, const T& y) : y(y) {this->x = x;}
            Vector2d(const Vector1d<T> & v) : y(0) {this->x = v.x;}
            Vector2d(const Vector2d<T> & v) : y(v.y) {this->x = v.x;}

            /** Default destructor */
            virtual ~Vector2d(){;}

            void setY(const T& v){y=v;}

            T getY()const{return y;}

            virtual float dot(const Vector2d<T>& v)const{return (this->x*v.x+y*v.y);}

            virtual float length()const                 {return sqrt(lengthSquared());}
            virtual float lengthSquared()const          {return (this->x*this->x + y*y);}
            virtual Vector2d<T> unit()
            {
                float len = length();
                if(len == 0)
                    return Vector2d<T> (0,1);

                float temp = 1/len;
                return Vector2d<T>(this->x*temp,this->y*temp);
            }
            virtual void normalise()                    {*this = unit();}

            virtual bool equals(const Vector1d<T>& v){return ((y == 0) && (this->x == v.x));}
            virtual bool equals(const Vector2d<T>& v){return ((this->x == v.x) && (y == v.y));}

        T y;
    };
}

#endif // VECTOR2DI_H