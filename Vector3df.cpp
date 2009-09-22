#include "Vector3df.h"

Vector3df::Vector3df()
{
    //ctor
}

void Vector3df::normalise()
{
    float temp = 1/length();
	if (temp <= std::numeric_limits<float>::max())
	{
		x *= temp;
		y *= temp;
		z *= temp;
	}
	else
	{
		x = 0.0f;
		y = 1.0f;
		z = 0.0f;
	}
}
