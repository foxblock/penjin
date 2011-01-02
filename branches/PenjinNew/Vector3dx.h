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
#ifndef VECTOR3DX_H
#define VECTOR3DX_H

#include "trenki/vector_math.h"        //  Vectors
#include "PenjinFixedFunc.h"
#include <limits>

using namespace vmath;
using namespace fixedpoint;

class Vector3dx : public vec3<fixed_point<16> >
{
    public:
        Vector3dx();
        template <class T>
        Vector3dx(const T& v){x = v.x;y = v.y; z = v.z;}

        template <class T>
        Vector3dx(const T& x,const T& y, const T& z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        template <class T,class S, class B>
        Vector3dx(const T& x,const S& y, const B& z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        /// Standard operators
        template <class T>
        Vector3dx& operator=(const T& v){x = v.x;y=v.y;z=v.z;return *this;}

        // TODO Add a level of approximation to equivalence operators.
        template <class T>
        bool operator==(const T& v)const{return (x==v.x && y==v.y && z==v.z);}

        template <class T>
        Vector3dx operator+(const T& v)const{return Vector3dx(x + v.x, y + v.y, z + v.z);}

        template <class T>
        Vector3dx operator-(const T& v)const{return Vector3dx(x - v.x, y - v.y,z-v.z);}


        template <class T>
        Vector3dx operator*(const T& v)const{return Vector3dx(x * v.x, y * v.y, z * v.z);}
        Vector3dx operator*(const float& f)const{return Vector3dx(x*f,y*f, z*f);}

        template <class T>
        Vector3dx operator/(const T& v)const{return Vector3dx(x / v.x, y / v.y, z/v.z);}
        Vector3dx operator/(const float& f)const{return Vector3dx(x/f,y/f,z/f);}

        template <class T>
        Vector3dx& operator+=(const T& v)
        {
            x+=v.x;
            y+=v.y;
            z+=v.z;
            return *this;
        }

        template <class T>
        Vector3dx& operator-=(const T& v)
        {
            x-=v.x;
            y-=v.y;
            z-=v.z;
            return *this;
        }

        template <class T>
        Vector3dx& operator*=(const T& v)
        {
            x*=v.x;
            y*=v.y;
            z*=v.z;
            return *this;
        }

        template <class T>
        Vector3dx& operator/=(const T& v)
        {
            x/=v.x;
            y/=v.y;
            z/=v.z;
            return *this;
        }
        /// Scaling
        Vector3dx& operator*=(const float& s){x*=s;y*=s;z*=s;return *this;}
        Vector3dx& operator/=(const float& s){x/=s;y/=s;z/=s;return *this;}
        /// Negation
        Vector3dx operator- (){return Vector3dx(0-x,0-y,0-z);}

        /// Vector operations
        Vector3dx unit()const{fixed_point<16> temp = length();return Vector3dx(x/temp,y/temp,z/temp);}
        template <class T>
        fixed_point<16> dot(const T& v)const{return (x*v.x+y*v.y+z*v.z);}
        fixed_point<16> length() const{return fixsqrt16(lengthSquared());}
        fixed_point<16> lengthSquared() const{return (x*x + y*y + z*z);}
        void normalise();

        //  TODO the following functions need implementing.
        Vector3dx normalisedCross(const Vector3dx& v);
        Vector3dx cross(const Vector3dx& v);

        const Vector3dx operator* ( float m[16] );
        const Vector3dx& operator*= ( float m[16] );

        //float* getVector();
};

#endif // VECTOR3DX_H
