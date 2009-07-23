#include "Vector2di.h"

void Vector2di::normalise()
{
    float temp = 1/length();
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
