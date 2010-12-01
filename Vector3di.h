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
#ifndef VECTOR3DI_H
#define VECTOR3DI_H

#include "trenki/vector_math.h"        //  Vectors
#include "PenjinFixedFunc.h"
#include <limits>

using namespace vmath;
using namespace fixedpoint;

class Vector3di : public vec3<int>
{
    public:
        Vector3di();
        template <class T>
        Vector3di(const T& v){x = v.x;y = v.y;z = v.z;}

        template <class T>
        Vector3di(const T& x,const T& y, const T& z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        template <class T,class S, class B>
        Vector3di(const T& x,const S& y, const B& z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        /// Standard operators
        template <class T>
        Vector3di& operator=(const T& v){x = v.x;y=v.y;z=v.z;return *this;}

        // TODO Add a level of approximation to equivalence operators.
        template <class T>
        bool operator==(const T& v)const{return (x==v.x && y==v.y && z==v.z);}

        template <class T>
        Vector3di operator+(const T& v)const{return Vector3di(x + v.x, y + v.y, z + v.z);}

        template <class T>
        Vector3di operator-(const T& v)const{return Vector3di(x - v.x, y - v.y,z-v.z);}


        template <class T>
        Vector3di operator*(const T& v)const{return Vector3di(x * v.x, y * v.y, z * v.z);}
        Vector3di operator*(const float& f)const{return Vector3di(x*f,y*f, z*f);}

        template <class T>
        Vector3di operator/(const T& v)const{return Vector3di(x / v.x, y / v.y, z/v.z);}
        Vector3di operator/(const float& f)const{return Vector3di(x/f,y/f,z/f);}

        template <class T>
        Vector3di& operator+=(const T& v)
        {
            x+=v.x;
            y+=v.y;
            z+=v.z;
            return *this;
        }

        template <class T>
        Vector3di& operator-=(const T& v)
        {
            x-=v.x;
            y-=v.y;
            z-=v.z;
            return *this;
        }

        template <class T>
        Vector3di& operator*=(const T& v)
        {
            x*=v.x;
            y*=v.y;
            z*=v.z;
            return *this;
        }

        template <class T>
        Vector3di& operator/=(const T& v)
        {
            x/=v.x;
            y/=v.y;
            z/=v.z;
            return *this;
        }
        /// Scaling
        Vector3di& operator*=(const float& s){x*=s;y*=s;z*=s;return *this;}
        Vector3di& operator/=(const float& s){x/=s;y/=s;z/=s;return *this;}
        /// Negation
        Vector3di operator- (){return Vector3di(0-x,0-y,0-z);}

        /// Vector operations
        Vector3di unit()const{fixed_point<16> temp = length();return Vector3di(fix2int(x/temp),fix2int(y/temp),fix2int(z/temp));}
        template <class T>
        #ifdef PENJIN_FIXED
            fixed_point<16> dot(const T& v)const{return (x*v.x+y*v.y+z*v.z);}
            fixed_point<16> length() const{return fixsqrt16(lengthSquared());}
            fixed_point<16> lengthSquared() const{return (x*x + y*y + z*z);}
        #else
            float dot(const T& v)const{return (x*v.x+y*v.y+z*v.z);}
            float length() const{return fixsqrt16(lengthSquared());}
            float lengthSquared() const{return (x*x + y*y + z*z);}
        #endif
        void normalise();

        //  TODO the following functions need implementing.
        Vector3di normalisedCross(const Vector3di& v);
        Vector3di cross(const Vector3di& v);

        const Vector3di operator* ( float m[16] );
        const Vector3di& operator*= ( float m[16] );

        //float* getVector();
};

#endif // VECTOR3DI_H
