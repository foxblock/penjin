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
