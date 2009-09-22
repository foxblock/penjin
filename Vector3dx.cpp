#include "Vector3dx.h"

Vector3dx::Vector3dx()
{
    //ctor
}

void Vector3dx::normalise()
{
    fixed_point<16> temp = 1/length();
	if (temp <= std::numeric_limits<float>::max())
	{
		x *= temp;
		y *= temp;
		z *= temp;
	}
	else
	{
		x = 0;
		y = 1;
		z = 0;
	}
}
