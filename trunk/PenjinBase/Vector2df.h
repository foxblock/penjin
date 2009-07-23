#ifndef VECTOR2DF_H
#define VECTOR2DF_H
#include "vector_math.h"        //  Vectors
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
