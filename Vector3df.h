#ifndef VECTOR3DF_H
#define VECTOR3DF_H

#include "trenki/vector_math.h"        //  Vectors
#include "PenjinFixedFunc.h"
#include <limits>

using namespace vmath;
using namespace fixedpoint;

class Vector3df : public vec3<float>
{
    public:
        Vector3df();
        template <class T>
        Vector3df(const T& v){x = v.x;y = v.y;z = v.z;}

        template <class T>
        Vector3df(const T& x,const T& y, const T& z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        template <class T,class S, class B>
        Vector3df(const T& x,const S& y, const B& z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        /// Standard operators
        Vector3df& operator=(const vec2<float>& v){x=v.x;y=v.y;return *this;}
        template <class T>
        Vector3df& operator=(const T& v){x = v.x;y=v.y;z=v.z;return *this;}
        Vector3df& operator=(const vec3<fixed_point<16> >& v){x = fix2float(v.x);y = fix2float(v.y);z = fix2float(v.z);return *this;}

        // TODO Add a level of approximation to equivalence operators.
        template <class T>
        bool operator==(const T& v)const{return (x==v.x && y==v.y && z==v.z);}
        bool operator==(const vec3<fixed_point<16> >& v)const{return(x == fix2float(v.x) && y == fix2float(v.y)&& z == fix2float(v.z));}
        template <class T>
        Vector3df operator+(const T& v)const{return Vector3df(x + v.x, y + v.y, z + v.z);}

        template <class T>
        Vector3df operator-(const T& v)const{return Vector3df(x - v.x, y - v.y,z-v.z);}


        template <class T>
        Vector3df operator*(const T& v)const{return Vector3df(x * v.x, y * v.y, z * v.z);}
        Vector3df operator*(const float& f)const{return Vector3df(x*f,y*f, z*f);}
        Vector3df operator*(const int& i)const{return Vector3df((float)i*x,(float)i*y,(float)i*z);}

        template <class T>
        Vector3df operator/(const T& v)const{return Vector3df(x / v.x, y / v.y, z/v.z);}
        Vector3df operator/(const float& f)const{return Vector3df(x/f,y/f,z/f);}

        template <class T>
        Vector3df& operator+=(const T& v)
        {
            x+=v.x;
            y+=v.y;
            z+=v.z;
            return *this;
        }

        template <class T>
        Vector3df& operator-=(const T& v)
        {
            x-=v.x;
            y-=v.y;
            z-=v.z;
            return *this;
        }

        template <class T>
        Vector3df& operator*=(const T& v)
        {
            x*=v.x;
            y*=v.y;
            z*=v.z;
            return *this;
        }

        template <class T>
        Vector3df& operator/=(const T& v)
        {
            x/=v.x;
            y/=v.y;
            z/=v.z;
            return *this;
        }
        Vector3df& operator/=(const int& i)
        {
            x/=i;
            y/=i;
            z/=i;
            return *this;
        }
        /// Scaling
        Vector3df& operator*=(const float& s){x*=s;y*=s;z*=s;return *this;}
        Vector3df& operator/=(const float& s){x/=s;y/=s;z/=s;return *this;}
        /// Negation
        Vector3df operator- (){return Vector3df(0-x,0-y,0-z);}

        /// Vector operations
        Vector3df unit()const{float temp = length();return Vector3df(x/temp,y/temp,z/temp);}
        template <class T>
        float dot(const T& v)const{return (x*v.x+y*v.y+z*v.z);}
        float dot(const vec3<fixed_point<16> >& v)const{return(x * fix2float(v.x) + y * fix2float(v.y) + z * fix2float(v.z));}
        float length() const{return sqrt(lengthSquared());}
        float lengthSquared() const{return (x*x + y*y + z*z);}
        void normalise();

        //  TODO the following functions need implementing.
        Vector3df normalisedCross(const Vector3df& v);
        Vector3df cross(const Vector3df& v);

        const Vector3df operator* ( float m[16] );
        const Vector3df& operator*= ( float m[16] );

        //float* getVector();
};

#endif // VECTOR3DF_H
