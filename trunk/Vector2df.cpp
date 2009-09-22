#include "Vector2df.h"

Vector2df::Vector2df()
{
    //ctor
}

void Vector2df::normalise()
{
    float temp = 1/length();
	if (temp <= std::numeric_limits<float>::max())
	{
		x *= temp;
		y *= temp;
	}
	else
	{
		x = 0.0f;
		y = 1.0f;
	}
}
