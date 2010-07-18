#ifndef INTVECTOR2D_H_INCLUDED
#define INTVECTOR2D_H_INCLUDED

#include <cmath>

#include "PenjinTypes.h"

class IntVector2d
{
    public:
        IntVector2d();             // Default vector
        IntVector2d(CRint x,CRint y);  // Create a vector at this x and y
        IntVector2d(const Vector2dx& vec){setXY(vec);}
        void setXY(const Vector2dx& vec){setXY(vec.x.intValue >> 16, vec.y.intValue >> 16);}
        void setXY(CRFixed x,CRFixed y)
        {
            setX(x.intValue >> 16);
            setY(y.intValue >> 16);
        }
        void setXY(CRint x, CRint y)
        {
            setX(x);
            setY(y);
        }
        void setX(CRint x){this->x = x;}
        void setY(CRint y){this-> y = y;}
        int getX() const {return x;}
        int getY() const {return y;}
        // OPERATORS
        bool operator==(IntVector2d& vector);   //   Check if two vectors are equal
        IntVector2d operator- ();               //   Perform negation if vector
        const IntVector2d& operator= ( const IntVector2d& vector );    // Assign value
        const IntVector2d& operator+= ( const IntVector2d& v );
        const IntVector2d& operator-= ( const IntVector2d& v );
        const IntVector2d& operator*= ( CRint s );
        const IntVector2d& operator/= ( CRint s );
        const IntVector2d operator+ ( const IntVector2d& v ) const;
        const IntVector2d operator- ( const IntVector2d& v ) const;
        const IntVector2d operator* ( CRint s ) const;
        const IntVector2d operator/ (int s) const;
        const int dot( const IntVector2d& v ) const;
        const uint length() const;
        const uint lengthSquared() const;
        const IntVector2d unit() const;
        void normalise();

        friend const IntVector2d operator* ( CRint s, const IntVector2d& v ){return v*s;}

        //IntVector2d normcrossprod(IntVector2d v);
        //IntVector2d crossprod(IntVector2d v);

        int* getVector();
    private:
        int x;
        int y;
};

#endif // INTVECTOR2D_H_INCLUDED
