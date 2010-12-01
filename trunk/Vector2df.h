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
#ifndef VECTOR2DF_H
#define VECTOR2DF_H
#include "trenki/vector_math.h"        //  Vectors
#include "PenjinFixedFunc.h"
#include <limits>

using namespace vmath;
using namespace fixedpoint;

class Vector2df : public vec2<float>
{
    public:
        /// Constructors and Deconstructor.
        Vector2df();
        Vector2df(const vec2<fixed_point<16> >& v){x = fix2float(v.x);y = fix2float(v.y);}
        template <class T>
        Vector2df(const T& v){x = v.x;y = v.y;}

        template <class T>
        Vector2df(const T& x,const T& y)
        {
            this->x = x;
            this->y = y;
        }
        template <class T,class S>
        Vector2df(const T& x,const S& y)
        {
            this->x = x;
            this->y = y;
        }

        /// Standard operators
        Vector2df& operator=(const vec2<fixed_point<16> >& v){x = fix2float(v.x);y = fix2float(v.y);return *this;}
        template <class T>
        Vector2df& operator=(const T& v){x = v.x;y=v.y;return *this;}
        Vector2df& operator=(const float& v){x = y = v;return *this;}


        // TODO Add a level of approximation to equivalence operators.
        template <class T>
        bool operator==(const T& v)const{return (x==v.x && y==v.y);}
        bool operator==(const vec2<fixed_point<16> >& v)const{return(x == fix2float(v.x) && y == fix2float(v.y));}
        template <class T>
        Vector2df operator+(const T& v)const{return Vector2df(x + v.x, y + v.y);}

        template <class T>
        Vector2df operator-(const T& v)const{return Vector2df(x - v.x, y - v.y);}


        template <class T>
        Vector2df operator*(const T& v)const{return Vector2df(x * v.x, y * v.y);}
        Vector2df operator*(const float& f)const{return Vector2df(x*f,y*f);}
        Vector2df operator*(const int& i)const{return Vector2df(x*i,y*i);}

        template <class T>
        Vector2df operator/(const T& v)const{return Vector2df(x / v.x, y / v.y);}
        Vector2df operator/(const float& f)const{return Vector2df(x/f,y/f);}

        template <class T>
        Vector2df& operator+=(const T& v)
        {
            x+=v.x;
            y+=v.y;
            return *this;
        }

        template <class T>
        Vector2df& operator-=(const T& v)
        {
            x-=v.x;
            y-=v.y;
            return *this;
        }

        template <class T>
        Vector2df& operator*=(const T& v)
        {
            x*=v.x;
            y*=v.y;
            return *this;
        }

        template <class T>
        Vector2df& operator/=(const T& v)
        {
            x/=v.x;
            y/=v.y;
            return *this;
        }
        /// Scaling
        Vector2df& operator*=(const float& s){x*=s;y*=s;return *this;}
        Vector2df& operator/=(const float& s){x/=s;y/=s;return *this;}
        /// Negation
        Vector2df operator- (){return Vector2df(0-x,0-y);}

        /// Vector operations
        Vector2df unit()const{float temp = length();return Vector2df(x/temp,y/temp);}
        template <class T>
        float dot(const T& v)const{return (x*v.x+y*v.y);}
        float dot(const vec2<fixed_point<16> >& v)const{return(x * fix2float(v.x) + y * fix2float(v.y));}
        float length() const{return sqrt(lengthSquared());}
        float lengthSquared() const{return (x*x + y*y);}
        void normalise();
};

#endif // VECTOR2DF_H
