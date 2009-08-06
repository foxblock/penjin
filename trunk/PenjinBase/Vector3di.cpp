#include "Vector3di.h"

Vector3di::Vector3di()
{
    //ctor
}

void Vector3di::normalise()
{
    #ifdef PENJIN_FIXED
        fixed_point<16> temp = (1/length());
	#else
        float temp = (1/length());
	#endif
	if (temp <= std::numeric_limits<float>::max())
	{
        #ifdef PENJIN_FIXED
            x *= fix2int(temp);
            y *= fix2int(temp);
            z *= fix2int(temp);
        #else
            x *= temp;
            y *= temp;
            z *= temp;
        #endif
	}
	else
	{
		x = 0;
		y = 1;
		z = 0;
	}
}
