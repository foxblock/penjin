#include "Vector3di.h"

Vector3di::Vector3di()
{
    //ctor
}

void Vector3di::normalise()
{
    fixed_point<16> temp = (1/length());
	if (temp <= std::numeric_limits<float>::max())
	{
		x *= fix2int(temp);
		y *= fix2int(temp);
		z *= fix2int(temp);
	}
	else
	{
		x = 0;
		y = 1;
		z = 0;
	}
}
