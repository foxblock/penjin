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
#ifndef VECTOR2DX_H
#define VECTOR2DX_H

#include "trenki/vector_math.h"        //  Vectors
#include "trenki/fixed_class.h"
#include <limits>

using namespace vmath;
using namespace fixedpoint;

class Vector2dx : public vec2<fixed_point<16> >
{
    public:
        /// Constructors and Deconstructor.
        Vector2dx();
        template <class T>
        Vector2dx(const T& v){x=v.x; y=v.y;}
        Vector2dx(const fixed_point<16>& x,const fixed_point<16>& y)
        {
            this->x = x;
            this->y = y;
        }
        Vector2dx(const int& x,const int& y)
        {
            this->x = x;
            this->y = y;
        }
        Vector2dx(const float& x,const float& y)
        {
            this->x = x;
            this->y = y;
        }
        /// Standard operators
        template <class T>
        Vector2dx& operator=(const T& v){x = v.x;y=v.y;return *this;}

        // TODO Add a level of approximation to equivalence operators.
        template <class T>
        bool operator==(const T& v)const{return (x==v.x && y==v.y);}
        template <class T>
        Vector2dx operator+(const T& v)const{return Vector2dx(x + v.x, y + v.y);}

        template <class T>
        Vector2dx operator-(const T& v)const{return Vector2dx(x - v.x, y - v.y);}


        template <class T>
        Vector2dx operator*(const T& v)const{return Vector2dx(x * v.x, y * v.y);}
        Vector2dx operator*(const fixed_point<16>& f)const{return Vector2dx((x*f),(y*f));}

        template <class T>
        Vector2dx operator/(const T& v)const{return Vector2df(x / v.x, y / v.y);}
        Vector2dx operator/(const fixed_point<16>& f)const{return Vector2dx(x/f,y/f);}

        template <class T>
        Vector2dx& operator+=(const T& v)
        {
            x+=v.x;
            y+=v.y;
            return *this;
        }

        template <class T>
        Vector2dx& operator-=(const T& v)
        {
            x-=v.x;
            y-=v.y;
            return *this;
        }

        template <class T>
        Vector2dx& operator*=(const T& v)
        {
            x*=v.x;
            y*=v.y;
            return *this;
        }
        Vector2dx& operator*=(const float& f)
        {
            x*=f;
            y*=f;
            return *this;
        }

        template <class T>
        Vector2dx& operator/=(const T& v)
        {
            x/=v.x;
            y/=v.y;
            return *this;
        }
        /// Scaling
        Vector2dx& operator*=(const vec2<fixed_point<16> >& s);
        Vector2dx& operator/=(const vec2<fixed_point<16> >& s);
        /// Negation
        Vector2dx operator- (){return Vector2dx(0-x,0-y);}

        /// Vector operations
        Vector2dx unit()const{fixed_point<16> temp = length();return Vector2dx(x/temp,y/temp);}
        template <class T>
        fixed_point<16> dot(const T& v)const{return (x*v.x+y*v.y);}
        fixed_point<16> length() const{return fixsqrt16(lengthSquared().intValue);}
        fixed_point<16> lengthSquared() const{return (x*x + y*y);}
        void normalise();
};
#endif // VECTOR2DX_H
