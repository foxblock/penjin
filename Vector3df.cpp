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

Vector3df Vector3df::cross(const Vector3df& v)
{
	Vector3df temp;
	temp.x = y*v.z - z*v.y;
	temp.y = z*v.x - x*v.z;
	temp.z = x*v.y - y*v.x;
	return temp;
}

Vector3df Vector3df::normalisedCross(const Vector3df& v)
{
    Vector3df out = cross(v);
    out.normalise();
    return out;
}
