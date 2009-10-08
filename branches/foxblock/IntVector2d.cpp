#include "IntVector2d.h"

IntVector2d::IntVector2d()
{
   x = 0;
   y = 0;
}

IntVector2d::IntVector2d(CRint x, CRint y)
{
   this->x = x;
   this->y = y;
}

bool IntVector2d::operator==(IntVector2d& vec)
{
   return (x == vec.x && y == vec.y);
}

IntVector2d IntVector2d::operator- ()
{
   return(IntVector2d(0-x,0-y));
}

const IntVector2d& IntVector2d::operator=(const IntVector2d& vec)
{
   x = vec.x;
   y = vec.y;
   return *this;
}

const IntVector2d& IntVector2d::operator+= ( const IntVector2d& v )
{
	x += v.x;
	y += v.y;
	return *this;
}

const IntVector2d& IntVector2d::operator-= ( const IntVector2d& v )
{
	x -= v.x;
	y -= v.y;
	return *this;
}

const IntVector2d& IntVector2d::operator*= ( CRint s )
{
	x*=s;
	y*=s;
	return *this;
}

const IntVector2d& IntVector2d::operator/= ( CRint s )
{
	x/=s;
	y/=s;
	return *this;
}

const IntVector2d IntVector2d::operator+ ( const IntVector2d& v ) const
{
	return IntVector2d(x+v.x,y+v.y);
}

const IntVector2d IntVector2d::operator- ( const IntVector2d& v ) const
{
	return IntVector2d(x-v.x,y-v.y);
}

const IntVector2d IntVector2d::operator* ( CRint s ) const
{
	return IntVector2d(x*s,y*s);
}

const IntVector2d IntVector2d::operator/ (int s) const
{
	return IntVector2d(x/s,y/s);
}

const int IntVector2d::dot( const IntVector2d& v ) const
{
	return (x*v.x+y*v.y);
}

const uint IntVector2d::length() const
{
	return ( (uint)sqrt((float)lengthSquared()) );
}

const uint IntVector2d::lengthSquared() const
{
	return ( x*x + y*y );
}

const IntVector2d IntVector2d::unit() const
{
	int temp = length();
	return IntVector2d(x/temp,y/temp);
}

void IntVector2d::normalise()
{
	int temp = length();

		x /= temp;
		y /= temp;
}


int * IntVector2d::getVector()
{
	int* temp = new int[2];

	temp[0] = x;
	temp[1] = y;

	return temp;
}


