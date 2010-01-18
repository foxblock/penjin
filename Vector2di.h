#ifndef VECTOR2DI_H
#define VECTOR2DI_H

#include "trenki/vector_math.h"        //  Vectors
#include "PenjinFixedFunc.h"
#include <limits>

using namespace vmath;
using namespace fixedpoint;
#include "Vector2dx.h"


class Vector2di : public vec2<int>
{
    public:
        /// Constructors and Deconstructor.
        Vector2di(){;}
        template <class T>
        Vector2di(const T& v){x = v.x;y = v.y;}
        Vector2di(const vec2<fixed_point<16> >& v)
        {
            this->x = fixedpoint::fix2int(v.x);
            this->y = fixedpoint::fix2int(v.y);
        }
        Vector2di(const Vector2dx& v)
        {
            vec2<fixed_point<16> > t = v;
            this->x = fixedpoint::fix2int(t.x);
            this->y = fixedpoint::fix2int(t.y);
        }
        Vector2di(const fixed_point<16>& x, const fixed_point<16>& y)
        {
            this->x = fixedpoint::fix2int(x);
            this->y = fixedpoint::fix2int(y);
        }
        template <class T>
        Vector2di(const T& x,const T& y)
        {
            this->x = x;
            this->y = y;
        }
        template <class T,class S>
        Vector2di(const T& x,const S& y)
        {
            this->x = x;
            this->y = y;
        }

        /// Standard operators
        Vector2di& operator=(const vec2<fixed_point<16> >& v){x = fix2int(v.x);y = fix2int(v.y);return *this;}
        template <class T>
        Vector2di& operator=(const T& v){x = v.x;y=v.y;return *this;}

        // TODO Add a level of approximation to equivalence operators.
        template <class T>
        bool operator==(const T& v)const{return (x==v.x && y==v.y);}
        bool operator==(const vec2<fixed_point<16> >& v)const{return(x == fix2int(v.x) && y == fix2int(v.y));}
        template <class T>
        Vector2di operator+(const T& v)const{return Vector2di(x + v.x, y + v.y);}

        template <class T>
        Vector2di operator-(const T& v)const{return Vector2di(x - v.x, y - v.y);}


        template <class T>
        Vector2di operator*(const T& v)const{return Vector2di(x * v.x, y * v.y);}
        Vector2di operator*(const float& f)const{return Vector2di(x*f,y*f);}

        template <class T>
        Vector2di operator/(const T& v)const{return Vector2di(x / v.x, y / v.y);}
        // TODO add rounding up
        Vector2di operator/(const float& f)const{return Vector2di(x/f,y/f);}
        // TODO use a Fixed intermediary to round to nearest whole number for result.
        Vector2di operator/(const int& i)const{return Vector2di(x/i,y/i);}

        template <class T>
        Vector2di& operator+=(const T& v)
        {
            x+=v.x;
            y+=v.y;
            return *this;
        }

        template <class T>
        Vector2di& operator-=(const T& v)
        {
            x-=v.x;
            y-=v.y;
            return *this;
        }
        Vector2di& operator-=(const vec2<fixed_point<16> >& v)
        {
            x-=fixedpoint::fix2int(v.x);
            y-=fixedpoint::fix2int(v.y);
            return *this;
        }
        Vector2di& operator-=(const Vector2dx& v)
        {
            x-=fixedpoint::fix2int(v.x);
            y-=fixedpoint::fix2int(v.y);
            return *this;
        }
        template <class T>
        Vector2di& operator*=(const T& v)
        {
            x*=v.x;
            y*=v.y;
            return *this;
        }

        template <class T>
        Vector2di& operator/=(const T& v)
        {
            x/=v.x;
            y/=v.y;
            return *this;
        }
        Vector2di& operator/=(const int& i)
        {
            // TODO added Fixed intermediary and round result to nearest whole number.
            x/=i;
            y/=i;
            return *this;
        }
        /// Scaling
        Vector2di& operator*=(const float& s);
        Vector2di& operator/=(const float& s);
        /// Negation
        Vector2di operator- (){return Vector2di(0-x,0-y);}

        /// Vector operations
        Vector2di unit()const{float temp = length();return Vector2di(x/temp,y/temp);}
        template <class T>
        float dot(const T& v)const{return (x*v.x+y*v.y);}
        float dot(const vec2<fixed_point<16> >& v)const{return(x * fix2float(v.x) + y * fix2float(v.y));}
        float length() const{return sqrt(lengthSquared());}
        float lengthSquared() const{return (x*x + y*y);}
        void normalise();
};

#endif // VECTOR2DI_H
