#include "Vector2dx.h"

Vector2dx::Vector2dx()
{
    //ctor
}

void Vector2dx::normalise()
{
    fixed_point<16> temp = 1/length();
	if (temp <= std::numeric_limits<float>::max())
	{
		x *= temp;
		y *= temp;
	}
	else
	{
		x = 0;
		y = 1;
	}
}
